 #include "minitalk.h"

volatile pid_t g_c_pid = 0;

unsigned char *ft_dup_c(unsigned char c)
{
    unsigned char *p;
	p = malloc(sizeof(unsigned char));
    if (!p)
        return NULL;
    *p = c;
    return p;
}

static void ft_lst_to_s(t_list *lst)
{
	t_list *tmp;
	char *line;
	int				i;
	if (!lst)
		return ;
	tmp = NULL;
	tmp = lst;
	line = ft_calloc((ft_lstsize(lst) + 2), sizeof(char));
	if (!line)
		return ;
	i = 0;
	while (tmp)
	{
		line[i++] = *((unsigned char *)tmp->content);
		tmp = tmp->next;
	}
	line[i] = '\n';
	ft_putstr_fd(line, 1);
	free(line);
}

// void ft_handle_message(t_list *message)
// {
// 	if(!message)
// 		return ;
	
// }

void handler_signal(int sig, siginfo_t* info, void *context)
{
	static int bit = 0;
	static unsigned char c = 0;
	static t_list *message = NULL;
	(void) context;
	if(g_c_pid == 0)
		g_c_pid = info->si_pid;
	ft_printf("Received signal: %s\n", (sig == SIGUSR2) ? "SIGUSR2" : "SIGUSR1");
	if(sig == SIGUSR2)
		c |= (1 << bit);
	printf("ok 1 || gc pid: %u\n", g_c_pid);
	if(++bit == 8)
	{
		printf("%c\n", c);
		if(c == '\0')
		{
			ft_lst_to_s(message);
			ft_lstclear(&message, free);
			message = NULL;
			kill(g_c_pid, SIGUSR2);
			printf("ok display\n");
			bit = 0;
			c = 0;
            g_c_pid = 0;
			return ;
		}
		else
			ft_lstadd_back(&message, (ft_lstnew(ft_dup_c(c))));
		bit = 0;
		c = 0;
		printf("ok 2\n");
		
	}
	// Check if the PID is still valid before sending a signal
    if (kill(g_c_pid, 0) == -1)  // 0 does not send a signal, but checks if the process exists
    {
		ft_printf("kill failed\n");
        if (errno == ESRCH)
        {
            // The client process doesn't exist anymore
            ft_printf("Client disconnected or terminated. Stopping communication.\n");
            g_c_pid = 0;
            return;
        }

    }
	kill(g_c_pid, SIGUSR1);
	printf("ok 3\n");
}

int main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = &handler_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGUSR1, &sa, NULL) == -1)
		hand_error("Error SIGUSR1 server");
	if(sigaction(SIGUSR2, &sa, NULL) == -1)
		hand_error("Error SIGUSR2 server");
	ft_printf("Server PID: %d\n", getpid());
	while(1)
		pause();
	return (0);
}

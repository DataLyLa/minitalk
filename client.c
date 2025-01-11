#include "minitalk.h"

volatile int g_received = 0;

void sig_handler(int sig, siginfo_t* info, void *context)
{
	(void)context;
	(void)info;
	if(sig == SIGUSR2)
		ft_printf("Message fully received\n");
	g_received = 1;
}

void send_char(int server_pid, unsigned char c)
{
	int i;

	i = -1;
	while (++i < 8)
	{
		if((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		while(!g_received)
			pause();
		g_received = 0;
	}
}

void send_message(int server_pid, const char *message)
{
	while(*message)
	{
		send_char(server_pid, *message);
		message++;
	}
	send_char(server_pid, '\0');
}

int main(int ac, char **av)
{
	struct sigaction sa;
	int server_pid;
	char *s;
	int n;
	g_received = 0;
	if(ac != 3)
	{
		ft_putstr_fd("Usage : ./client [SERVER_PID] [MESSAGE]", 2);
		return (0);
	}
	sa.sa_sigaction = &sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGUSR1, &sa, NULL) == -1)
		hand_error("Error SIGUSR1 server");
	if(sigaction(SIGUSR2, &sa, NULL) == -1)
		hand_error("Error SIGUSR1 server");
	n = ft_atoi(av[1]);
	server_pid = n;
	s = av[2];
	if(server_pid <= 0)
		ft_printf("[ ERROR ] wrong PID enter.. Please write the server pid");
	if(ft_strlen(av[2]) == 0)
		ft_printf("Nothing to send, ...Please write something");
	send_message(server_pid, s);
	return (0);
}

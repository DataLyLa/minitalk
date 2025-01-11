/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:18:29 by lylaurol          #+#    #+#             */
/*   Updated: 2025/01/11 21:25:17 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_c_pid = 0;

unsigned char	*ft_dup_c(unsigned char c)
{
	unsigned char	*p;

	p = malloc(sizeof(unsigned char));
	if (!p)
		return (NULL);
	*p = c;
	return (p);
}

static void	ft_lst_to_s(t_list *lst)
{
	t_list		*tmp;
	char		*line;
	int			i;

	if (!lst)
		return ;
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

void	handler_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	c = 0;
	static t_list			*message = NULL;

	(void) context;
	if (g_c_pid == 0)
		g_c_pid = info->si_pid;
	if (sig == SIGUSR2)
		c |= (1 << bit);
	if (++bit == 8)
	{
		bit = 0;
		if (c == '\0')
		{
			ft_lst_to_s(message);
			kill(g_c_pid, SIGUSR2);
			ft_lstclear(&message, free);
			g_c_pid = 0;
			return ;
		}
		else
			ft_lstadd_back(&message, (ft_lstnew(ft_dup_c(c))));
		c = 0;
	}
	kill(g_c_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handler_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		hand_error("Error SIGUSR1 server");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		hand_error("Error SIGUSR2 server");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}

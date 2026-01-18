/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutucir <rlutucir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:38:35 by rlutucir          #+#    #+#             */
/*   Updated: 2026/01/18 18:16:21 by rlutucir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	i = 0;

	(void)context;
	if (sig == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (i == 0)
			write(1, "\n", 1);
		else
			write(1, &i, 1);
		bit = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_action;

	pid = getpid();
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	s_action.sa_sigaction = handler;
	s_action.sa_flags = SA_SIGINFO;
	sigemptyset(&s_action.sa_mask);
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);
	while (1)
		pause();
	return (0);
}

// int main(void)
// {
//     struct sigaction sa;
//     int pid;

//     // Clear the structure and set the handler function
//     sa.sa_handler = &handler;
//     sa.sa_flags = 0; // Standard handling
//     sigemptyset(&sa.sa_mask); // Don't block any other signals during the handler

//     // Bind SIGUSR1 and SIGUSR2 to our handler
//     sigaction(SIGUSR1, &sa, NULL);
//     sigaction(SIGUSR2, &sa, NULL);

//     // Print PID so the client knows where to send
//     // ... code to print getpid() ...
//     pid = getpid();
//     ft_putstr_fd("PID: ", 1);
//     ft_putnbr_fd(pid, 1);
//     ft_putchar_fd('\n', 1);

//     while (1)
//         pause(); // Wait for signals efficiently
//     return (0);
// }
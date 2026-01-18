/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutucir <rlutucir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:37:24 by rlutucir          #+#    #+#             */
/*   Updated: 2026/01/18 16:29:20 by rlutucir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	confirmation_received;

static void	ack_handler(int sig)
{
	(void)sig; 
	confirmation_received = 1;
}

void	check_bytes(int pid, unsigned char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		confirmation_received = 0;
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return ;
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return ;
		}
		bit++;
		while (!confirmation_received)
			pause();
	}
}

int	main(int ac, char **av)
{
	int				pid;
	int				i;
	struct sigaction	sa;

	if (ac != 3)
	{
		ft_putstr_fd("Error\nUsage: ./client <PID_SERVER> <text>\n", 1);
		return (1);
	}
	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	pid = ft_atoi(av[1]);
	if (!pid)
	{
		ft_putstr_fd("Incorrect PID\n", 1);
		return (1);
	}
	i = 0;
	while (av[2][i])
		check_bytes(pid, av[2][i++]);
	check_bytes(pid, '\0');
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutucir <rlutucir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:37:24 by rlutucir          #+#    #+#             */
/*   Updated: 2026/01/18 18:15:49 by rlutucir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_confirmation_received;

static void	ack_handler(int sig)
{
	(void)sig;
	g_confirmation_received = 1;
}

void	send_bytes(int pid, unsigned char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_confirmation_received = 0;
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putstr_fd("Error invalid PID\n", 1);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putstr_fd("Error invalid PID\n", 1);
				exit(1);
			}
		}
		bit++;
		while (!g_confirmation_received)
			pause();
	}
}

int	main(int ac, char **av)
{
	int					pid;
	int					i;

	if (ac != 3)
	{
		ft_putstr_fd("Error\nUsage: ./client <PID_SERVER> <text>\n", 1);
		return (1);
	}
	signal(SIGUSR1, ack_handler);
	pid = ft_atoi(av[1]);
	i = 0;
	while (av[2][i])
		send_bytes(pid, av[2][i++]);
	send_bytes(pid, '\0');
	return (0);
}
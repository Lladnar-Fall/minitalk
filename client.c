/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutucir <rlutucir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:37:24 by rlutucir          #+#    #+#             */
/*   Updated: 2026/01/13 01:51:55 by rlutucir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void check_bytes(int pid, unsigned char c)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if ((c >> bit) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        bit++;
        usleep(800);
    }
}

int main(int ac, char **av)
{
    int pid;
    int i;
    
    if (ac != 3)
        return (1);
    pid = ft_atoi(av[1]);
    if (!pid)
        return (1);
    i = 0;
    while (av[2][i])
        check_bytes(pid, av[2][i++]);
    check_bytes(pid, '\0');
}

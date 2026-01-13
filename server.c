/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutucir <rlutucir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:38:35 by rlutucir          #+#    #+#             */
/*   Updated: 2026/01/12 20:51:09 by rlutucir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handler(int sig)
{
    static int bit = 0;
    static unsigned char i = 0;

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
}

int main()
{
    int pid;

    pid = getpid();
    ft_putstr_fd("PID: ", 1);
    ft_putnbr_fd(pid, 1);
    ft_putchar_fd('\n', 1);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    while(1)
        pause();
    return (0);
}
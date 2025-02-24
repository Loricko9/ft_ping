/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:11:03 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/24 17:18:37 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_log(struct timeval *time)
{
	double	res;

	res = (time[1].tv_sec - time[0].tv_sec) * 1000.0 + (time[1].tv_usec - time[0].tv_usec) / 1000.0;
	printf("%d bytes from truc: icmp_seq=0 ttl=64 time=%.3f ms\n", PACKET_SIZE, res);
}

struct timeval	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

int	init_socket(void)
{
	int	socketfd;

	socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (socketfd < 0)
	{
		perror("Socket error");
		exit(1);
	}
	return (socketfd);
}

void	stop_ping(int signum)
{
	(void)signum;
	g_stop = false;
}

bool	init_signal(void)
{
	if (signal(SIGINT, stop_ping) == SIG_ERR)
	{
		perror("ft_ping");
		return (true);
	}
	return (false);
}

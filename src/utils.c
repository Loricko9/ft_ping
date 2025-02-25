/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:11:03 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/25 11:48:38 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_log(struct timeval *time, struct icmp *icmp, struct sockaddr_in *dest)
{
	double		res;
	char		host[INET_ADDRSTRLEN];

	if (inet_ntop(AF_INET, &(dest->sin_addr), host, INET_ADDRSTRLEN) == NULL)
		perror("inet_ntop");
	res = (time[1].tv_sec - time[0].tv_sec) * 1000.0 + (time[1].tv_usec - time[0].tv_usec) / 1000.0;
	printf("%d bytes from %s: icmp_seq=%d ttl=64 time=%.3f ms\n", PACKET_SIZE, host, icmp->icmp_seq, res);
}

void	print_stat(int *i, struct sockaddr_in *dest)
{
	char		host[INET_ADDRSTRLEN];

	if (inet_ntop(AF_INET, &(dest->sin_addr), host, INET_ADDRSTRLEN) == NULL)
		perror("inet_ntop");
	printf("--- %s ft_ping statistics ---\n", host);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", i[0], i[0] - i[1], (i[1] / i[0]) * 100);
}

int	init_socket(void)
{
	struct timeval	timeout;
	int				socketfd;

	socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (socketfd < 0)
	{
		perror("Socket error");
		exit(1);
	}
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
		perror("Set socket option");
		ft_free(socketfd);
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

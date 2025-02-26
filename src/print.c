/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:48:14 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/26 15:46:09 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_log(struct timeval *time, struct icmp *icmp,
	struct sockaddr_in *dest, char *recv_pkg)
{
	struct ip	*recv_header;
	double		res_time;
	char		host[INET_ADDRSTRLEN];

	recv_header = (struct ip*)recv_pkg;
	if (inet_ntop(AF_INET, &(dest->sin_addr), host, INET_ADDRSTRLEN) == NULL)
		perror("inet_ntop");
	res_time = (time[1].tv_sec - time[0].tv_sec) * 1000.0 + (time[1].tv_usec - time[0].tv_usec) / 1000.0;
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", PACKET_SIZE, host, icmp->icmp_seq, recv_header->ip_ttl, res_time);
}

void	print_stat(int *i, struct sockaddr_in *dest)
{
	char		host[INET_ADDRSTRLEN];

	if (inet_ntop(AF_INET, &(dest->sin_addr), host, INET_ADDRSTRLEN) == NULL)
		perror("inet_ntop");
	printf("--- %s ft_ping statistics ---\n", host);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", i[0], i[0] - i[1], (i[1] / i[0]) * 100);
}

void	print_start(char *address, struct sockaddr_in *dest_ip)
{
	char	ip_str[INET_ADDRSTRLEN];

	if (inet_ntop(AF_INET, &(dest_ip->sin_addr), ip_str, INET_ADDRSTRLEN) == NULL)
		perror("inet_ntop");
	printf("FT_PING %s (%s): 56 data bytes\n", address, ip_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   package.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:29:21 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/24 17:14:43 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short checksum(void *pckg, size_t len)
{
	unsigned short	*ptr;
	unsigned int	sum;

	ptr = pckg;
	sum = 0;
	while (len > 1)
	{
		sum += *(ptr++);
		len -= 2; 
	}
	if (len == 1)
		sum += *(unsigned char *)ptr;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return ((unsigned short)~sum);
}

bool	check_ip(struct sockaddr_in *ip_addr, char *address)
{
	memset(ip_addr, 0, sizeof(*ip_addr));
	ip_addr->sin_family = AF_INET;
	if (inet_pton(AF_INET, address, &ip_addr->sin_addr) <= 0)
	{
		printf("ping: unknown host\n");
		return (true);
	}
	return (false);
}

void	create_icmp(struct icmp *icmp, int seq)
{
	memset(icmp, 0, sizeof(*icmp));
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = getpid();
	icmp->icmp_seq = seq;
	icmp->icmp_cksum = checksum(icmp, sizeof(*icmp));
}

bool	loop_pkg(int socket, struct sockaddr_in *dest, size_t len, char *pkg)
{
	struct sockaddr_in	revc_ip;
	socklen_t			ip_len;
	char				recv_pkg[PACKET_SIZE];
	struct timeval		time[2];
	
	ip_len = sizeof(revc_ip);
	time[0] = get_time();
	printf("ip : %d\n", socket);
	if (sendto(socket, pkg, len, 0, (struct sockaddr *)dest, sizeof(*dest)) <= 0)
		return (perror("ft_ping"), true);
	if (recvfrom(socket, recv_pkg, sizeof(recv_pkg), 0, (struct sockaddr *)&revc_ip, &ip_len) <= 0)
		return (perror("ft_ping"), true);
	time[1] = get_time();
	print_log(time);
	return (false);
}

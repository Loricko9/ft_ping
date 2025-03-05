/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   package.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:29:21 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/05 17:38:59 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short	checksum(void *pckg, size_t len)
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
	return ((unsigned short) ~sum);
}

bool	convert_hostname(struct sockaddr_in *ip_addr, char *address)
{
	struct addrinfo	hint;
	struct addrinfo	*res;
	int				ret;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_RAW;
	ret = getaddrinfo(address, NULL, &hint, &res);
	if (ret != 0)
	{
		printf("ft_ping: unknown host\n");
		return (true);
	}
	memcpy(ip_addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);
	return (false);
}

bool	check_ip(struct sockaddr_in *ip_addr, char *address)
{
	memset(ip_addr, 0, sizeof(*ip_addr));
	ip_addr->sin_family = AF_INET;
	if (inet_pton(AF_INET, address, &ip_addr->sin_addr) <= 0)
		if (convert_hostname(ip_addr, address))
			return (true);
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

bool	check_pkg(char *recv_pkg, bool flag)
{
	struct ip	*ip_header;
	struct icmp	*icmp_header;
	char		host[INET_ADDRSTRLEN];

	ip_header = (struct ip *)recv_pkg;
	
	icmp_header = (struct icmp *)(recv_pkg + (ip_header->ip_hl << 2));
	if (inet_ntop(AF_INET, &(ip_header->ip_src), host, INET_ADDRSTRLEN) == NULL)
		perror("inet_ntop");
	if (icmp_header->icmp_type == ICMP_ECHOREPLY
		|| icmp_header->icmp_type == ICMP_ECHO)
		return (false);
	if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED)
		printf("92 bytes from %s : Times to lives exceeded\n", host);
	if (flag)
		printf("coucou\n");
	return (true);
}

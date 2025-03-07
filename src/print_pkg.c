/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pkg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:45:56 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/07 16:45:56 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_pkg2(struct iphdr *ip_header)
{
	char		ip_src[INET_ADDRSTRLEN];
	char		ip_dst[INET_ADDRSTRLEN];
	uint16_t	frag_off;

	if (inet_ntop(AF_INET, &(ip_header->daddr), ip_src, INET_ADDRSTRLEN)
		== NULL)
		perror("inet_ntop");
	if (inet_ntop(AF_INET, &(ip_header->saddr), ip_dst, INET_ADDRSTRLEN)
		== NULL)
		perror("inet_ntop");
	printf("\nVr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      ");
	printf("Dst     Data\n");
	printf(" %d  %d  %02d %04d %d   ", ip_header->version, ip_header->ihl,
		ip_header->tos, ntohs(ip_header->tot_len), ntohs(ip_header->id));
	frag_off = ntohs(ip_header->frag_off);
	printf("%d %04d", frag_off >> 13, frag_off & 0x1fff);
	printf("  %02d  %02d  %04x %s  %s\n", ip_header->ttl, ip_header->protocol,
		ntohs(ip_header->check), ip_src, ip_dst);
}

void	print_pkg(unsigned char *recv_pkg, struct icmp *icmp)
{
	size_t			i;
	struct iphdr	*ip_header;

	printf("IP Hdr Dump:\n ");
	i = -1;
	while (++i < sizeof(struct iphdr))
	{
		printf("%02x", recv_pkg[i]);
		if (i % 2)
			printf(" ");
	}
	ip_header = (struct iphdr *)recv_pkg;
	print_pkg2(ip_header);
	printf("ICMP: type %d, code 0, size %d, id 0x%04x, seq 0x%04x\n",
		icmp->icmp_type, PACKET_SIZE, icmp->icmp_id, icmp->icmp_seq);
}

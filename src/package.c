/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   package.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:29:21 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/21 17:25:19 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool	check_ip(struct sockaddr_in *ip_addr, char *address, struct icmp *head)
{
	memset(ip_addr, 0, sizeof(*ip_addr));
	ip_addr->sin_family = AF_INET;
	if (inet_pton(AF_INET, address, &ip_addr->sin_addr) <= 0)
	{
		printf("ping: unknown host\n");
		return (true);
	}
	memset(head, 0, sizeof(*head));
	head->icmp_type = ICMP_ECHO;
	head->icmp_code = 0;
	head->icmp_id = getpid();
	head->icmp_seq = 1;
	//head->icmp_cksum = 
}

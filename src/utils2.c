/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:48:14 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/26 14:52:25 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	ft_free(int fd)
{
	close(fd);
}

struct timeval	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

void	print_start(char *address, struct sockaddr_in *dest_ip)
{
	char	ip_str[INET_ADDRSTRLEN];

	if (inet_ntop(AF_INET, &(dest_ip->sin_addr), ip_str, INET_ADDRSTRLEN) == NULL)
		perror("inet_ntop");
	printf("FT_PING %s (%s): 56 data bytes\n", address, ip_str);
}

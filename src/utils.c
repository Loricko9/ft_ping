/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:11:03 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/21 16:53:56 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	init_socket(void)
{
	int	socketfd;

	socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
	if (socketfd < 0)
	{
		perror("Socket error");
		exit(1);
	}
	return (socketfd);
}

void	stop_ping(int signum)
{
	printf("salut\n");
}

void	init_signal(void)
{
	if (signal(SIGINT, stop_ping) == SIG_ERR)
	{
		perror("minishell");
		exit(1);
	}
}

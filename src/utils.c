/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:11:03 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/23 13:50:38 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	ft_free(void *ptr1, void *ptr2, int fd)
{
	// if (ptr1 != NULL)
	// 	free(ptr1);
	// if (ptr2 != NULL)	
	// 	free(ptr2);
	(void)ptr1;
	(void)ptr2;
	if (fd)
		close(fd);
}

long	get_time(void)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * 1000) + (end.tv_usec / 1000));
}

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
	(void)signum;
	g_stop = false;
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

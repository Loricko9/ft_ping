/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:11:03 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/10 11:08:37 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	ft_free(int fd, t_lst *lst)
{
	t_lst	*next;
	t_lst	*act;
	
	close(fd);
	init_signal(false);
	act = lst;
	while (act)
	{
		next = act->next;
		free(act);
		act = next;
	}
}

struct timeval	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

int	init_socket(void)
{
	struct timeval	timeout;
	int				socketfd;
	int				ttl;

	socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (socketfd < 0)
	{
		perror("Socket error");
		exit(1);
	}
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	ttl = TTL_SIZE;
	if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
			sizeof(timeout)) < 0 || setsockopt(socketfd, IPPROTO_IP, IP_TTL,
			&ttl, sizeof(ttl)) < 0)
	{
		perror("Setsocket option");
		ft_free(socketfd, NULL);
		exit(1);
	}
	return (socketfd);
}

void	stop_ping(int signum)
{
	(void)signum;
	g_stop = false;
}

bool	init_signal(bool func)
{
	if (func)
	{
		if (signal(SIGINT, stop_ping) == SIG_ERR)
		{
			perror("ft_ping");
			return (true);
		}
	}
	else
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		{
			perror("ft_ping");
			return (true);
		}
	}
	return (false);
}

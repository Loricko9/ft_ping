/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:54:15 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/21 17:24:40 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool	g_stop;

void	start_ping(char *host)
{
	int socketfd;
	struct sockaddr_in	dest_ip;
	struct icmp			header_pkg;

	socketfd = init_socket();
	if (check_ip(&dest_ip, host, &header_pkg))
		return ;
	
}

int main(int ac, char **av)
{
	int i;
	
	if (ac < 2)
	{
		printf("ping: missing host operand\nTry \'ping -?\' or \'ping --help\'\n");
		exit(1);
	}
	if (check_flags(ac, av))
		printf("coucou");
	init_signal();
	i = 0;
	while (++i < ac)
	{
		g_stop = true;
		if (av[i][0] != '-')
			start_ping(av[i]);
	}
}

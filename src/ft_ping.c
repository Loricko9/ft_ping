/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:54:15 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/24 17:08:59 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool	g_stop;

void	start_ping(char *host, int socketfd)
{
	struct sockaddr_in	dest_ip;
	struct icmp			pkg_icmp;
	char				pkg[PACKET_SIZE];
	int					i;

	if (check_ip(&dest_ip, host))
		return (ft_free(socketfd));
	printf("host : %s\n", host);
	if (init_signal())
		return (ft_free(socketfd));
	i = 0;
	while (g_stop)
	{
		create_icmp(&pkg_icmp, i);
		memcpy(pkg, &pkg_icmp, sizeof(pkg_icmp));
		if (loop_pkg(socketfd, &dest_ip, sizeof(pkg_icmp), pkg))
			return (ft_free(socketfd));
		i++;
		sleep(1);
	}
	printf("stop\n");
	ft_free(socketfd);
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
	i = 0;
	while (++i < ac)
	{
		g_stop = true;
		if (av[i][0] != '-')
			start_ping(av[i], init_socket());
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:54:15 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/25 11:47:48 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool	g_stop;

/*i[0] => send pkg | i[1] => lost pkg*/
void	start_ping(char *host, int socketfd)
{
	struct sockaddr_in	dest_ip;
	struct icmp			pkg_icmp;
	char				pkg[PACKET_SIZE];
	int					i[2];

	if (check_ip(&dest_ip, host))
		return (ft_free(socketfd));
	if (init_signal())
		return (ft_free(socketfd));
	i[0] = 0;
	i[1] = 0;
	while (g_stop)
	{
		create_icmp(&pkg_icmp, i[0]);
		memcpy(pkg, &pkg_icmp, sizeof(pkg_icmp));
		if (loop_pkg(socketfd, &dest_ip, sizeof(pkg_icmp), pkg))
			i[1]++;
		i[0]++;
		sleep(1);
	}
	print_stat(i, &dest_ip);
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
		printf("FT_PING %s (ip): 56 data bytes\n", av[i]);
		if (av[i][0] != '-')
			start_ping(av[i], init_socket());
	}
	return (0);
}

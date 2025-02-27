/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:54:15 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/27 13:54:36 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool	g_stop;

/*i[0] => send pkg | i[1] => lost pkg*/
void	start_ping(char *host, int socketfd, bool flag)
{
	struct sockaddr_in	dest_ip;
	struct icmp			pkg_icmp;
	int					i[2];

	if (check_ip(&dest_ip, host))
		return (ft_free(socketfd));
	print_start(host, &dest_ip);
	if (init_signal(true))
		return (ft_free(socketfd));
	i[0] = 0;
	i[1] = 0;
	while (g_stop)
	{
		create_icmp(&pkg_icmp, i[0]);
		if (loop_pkg(socketfd, &dest_ip, &pkg_icmp, flag))
			i[1]++;
		i[0]++;
		sleep(1);
	}
	print_stat(i, &dest_ip);
	ft_free(socketfd);
}

int	main(int ac, char **av)
{
	int		i;
	bool	flag_v;

	if (ac < 2)
	{
		printf("ping: missing host operand\n");
		printf("Try \'ping -?\' or \'ping --help\'\n");
		exit(1);
	}
	flag_v = check_flags(ac, av);
	i = 0;
	while (++i < ac)
	{
		g_stop = true;
		if (av[i][0] != '-')
			start_ping(av[i], init_socket(), flag_v);
	}
	return (0);
}

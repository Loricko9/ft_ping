/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:54:15 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/10 11:11:45 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool	g_stop;

bool	loop_pkg(int socket, t_pkg_info *pkg_info, bool flag,
		t_lst **lst)
{
	struct sockaddr_in	revc_ip;
	socklen_t			pkg_len;
	unsigned char		recv_pkg[PACKET_SIZE + sizeof(struct ip)];
	unsigned char		send_pkg[PACKET_SIZE];
	struct timeval		time[2];

	memcpy(send_pkg, &pkg_info->icmp, sizeof(pkg_info->icmp));
	pkg_len = sizeof(revc_ip);
	time[0] = get_time();
	if (sendto(socket, send_pkg, sizeof(pkg_info->icmp), 0,
			(struct sockaddr *)&pkg_info->dest_ip, sizeof(pkg_info->dest_ip)) <= 0)
		return (perror("ft_ping"), true);
	if (recvfrom(socket, recv_pkg, sizeof(recv_pkg), 0,
			(struct sockaddr *)&revc_ip, &pkg_len) <= 0)
	{
		if (flag)
			print_err((struct icmp *)send_pkg, &pkg_info->dest_ip);
		return (true);
	}
	time[1] = get_time();
	if (check_pkg(recv_pkg, flag, sizeof(recv_pkg), &pkg_info->icmp))
		return (true);
	print_log(time, (struct icmp *)send_pkg, &pkg_info->dest_ip, recv_pkg);
	ft_lstaddback(lst, ft_newlst(time));
	return (false);
}

/*i[0] => send pkg | i[1] => lost pkg*/
void	start_ping(char *host, int socketfd, bool flag)
{
	t_pkg_info	pkg_info;
	t_lst		*lst;
	int			i[2];

	if (check_ip(&pkg_info.dest_ip, host))
		return (ft_free(socketfd, NULL));
	print_start(host, &pkg_info.dest_ip);
	if (init_signal(true))
		return (ft_free(socketfd, NULL));
	memset(i, 0, sizeof(i));
	lst = NULL;
	while (g_stop)
	{
		create_icmp(&pkg_info.icmp, i[0]);
		if (loop_pkg(socketfd, &pkg_info, flag, &lst))
			i[1]++;
		i[0]++;
		sleep(1);
	}
	print_stat(i, &pkg_info.dest_ip, lst);
	ft_free(socketfd, lst);
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

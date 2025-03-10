/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:55:27 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/10 11:38:40 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <netdb.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>
# include <netinet/in.h>

extern bool	g_stop;

# define PACKET_SIZE 64
# define TTL_SIZE 64

typedef struct s_pkg_info
{
	struct sockaddr_in	dest_ip;
	struct icmp			icmp;
}	t_pkg_info;

typedef struct s_lst
{
	double			time;
	struct s_lst	*next;
}	t_lst;

bool			loop_pkg(int socket, t_pkg_info *info, bool flag, t_lst **lst);

/*check_flags.c*/
bool			check_flags(int ac, char **av);

/*package.c*/
bool			check_ip(struct sockaddr_in *ip_addr, char *address);
void			create_icmp(struct icmp *icmp, int seq);
bool			check_pkg(unsigned char *recv_pkg, bool flag, size_t pkg_size,
					struct icmp *icmp_send);

/*utils.c*/
bool			init_signal(bool func);
int				init_socket(void);
void			ft_free(int fd, t_lst *lst);
struct timeval	get_time(void);

/*utils_lst.c*/
t_lst			*ft_newlst(struct timeval *time);
void			ft_lstaddback(t_lst **lst, t_lst *new);
double			get_min(t_lst *lst);
double			get_max(t_lst *lst);
double			get_avrg(t_lst *lst);

/*print.c*/
void			print_log(struct timeval *time, struct icmp *icmp,
					struct sockaddr_in *dest, unsigned char *recv_pkg);
void			print_start(char *address, struct sockaddr_in *dest_ip);
void			print_err(struct icmp *icmp, struct sockaddr_in *dest);
void			print_stat(int *i, struct sockaddr_in *dest, t_lst *lst);

/*print_pkg.c*/
void			print_pkg(unsigned char *recv_pkg, struct icmp *icmp);

#endif
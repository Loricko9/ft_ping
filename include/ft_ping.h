/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:55:27 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/23 13:45:14 by lle-saul         ###   ########.fr       */
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
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>

extern bool	g_stop;

# define PACKET_SIZE 64

/*check_flags.c*/
bool	check_flags(int ac, char **av);

/*package.c*/
bool	check_ip(struct sockaddr_in *ip_addr, char *address, struct icmp *head);

/*utils.c*/
void	ft_free(void *ptr1, void *ptr2, int fd);
long	get_time(void);
int		init_socket(void);
void	init_signal(void);

#endif
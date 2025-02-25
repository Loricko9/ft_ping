/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:25:46 by lle-saul          #+#    #+#             */
/*   Updated: 2025/02/25 10:57:43 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_help(void)
{
	printf("Usage: ft_ping [OPTION...] HOST ...\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
	printf("Options valid for all request types:\n\n");
	printf("-v, --verbose              verbose output\n");
	printf("-?, --help                 give this help list\n\n");
	printf("Mandatory or optional arguments to long options are also mandatory or optional\nfor any corresponding short options.\n");
	exit(0);
}

void	print_err_flag(char *err, bool type)
{
	if (type)
	printf("ft_ping: invalid option -- '%c'\n", err[0]);
	else
		printf("ft_ping: invalid option -- '%s'\n", err);
	printf("Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
	exit(64);
}

void check_flags_letter(char *str, bool *res)
{
	int i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '?')
			print_help();
		else if (str[i] == 'v')
			*res = true;
		else
			print_err_flag(&str[i], true);
	}
}

bool	check_flags(int ac, char **av)
{
	int		i;
	bool	res;

	i = 0;
	res = false;
	while(++i < ac)
	{
		if (av[i][0] && av[i][0] == '-' && av[i][1] && av[i][1] != '-')
			check_flags_letter(av[i], &res);
		else if (av[i][0] && av[i][1] && av[i][0] == '-' && av[i][1] == '-')
		{
			if (strcmp(av[i] + 2, "help") == 0)
				print_help();
			if (strcmp(av[i] + 2, "verbose") == 0)
				res = true;
			else
				print_err_flag(av[i], false);
		}
	}
	return (res);
}

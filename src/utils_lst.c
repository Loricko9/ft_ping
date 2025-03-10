/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:27:55 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/10 10:27:55 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_lst	*ft_newlst(struct timeval *time)
{
	t_lst	*new;
	double	res_time;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	res_time = (time[1].tv_sec - time[0].tv_sec) * 1000.0 + (time[1].tv_usec
			- time[0].tv_usec) / 1000.0;
	new->time = res_time;
	new->next = NULL;
	return (new);
}

void	ft_lstaddback(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

double	get_min(t_lst *lst)
{
	double	min;

	min = 1.7976931348623157e+308;
	while (lst)
	{
		if (lst->time < min)
			min = lst->time;
		lst = lst->next;
	}
	return (min);
}

double	get_max(t_lst *lst)
{
	double	max;

	max = 0.0;
	while (lst)
	{
		if (lst->time > max)
			max = lst->time;
		lst = lst->next;
	}
	return (max);
}

double	get_avrg(t_lst *lst)
{
	double	total;
	int		i;

	total = 0.0;
	i = 0;
	while (lst)
	{
		total += lst->time;
		i++;
		lst = lst->next;
	}
	return (total / (double)i);
}

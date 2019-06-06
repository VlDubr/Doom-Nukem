/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getlistindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:10:44 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/05 15:02:03 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_list		*getlistindex(t_list *list, size_t index)
{
	t_list	*tmp;
	t_list	*res;

	tmp = list;
	if (index == 0)
		return (list);
	while (tmp != NULL && index)
	{
		tmp = tmp->next;
		index--;
		if (index == 0)
			res = tmp;
	}
	return (res);
}

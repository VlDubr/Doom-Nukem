/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetelement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 12:19:07 by gdaniel           #+#    #+#             */
/*   Updated: 2019/03/18 12:19:07 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstgetelement(t_list *list, int element)
{
	int		e;
	t_list	*tmp;

	if (!list || element < 0)
		return (NULL);
	if (element == 0)
		return (list);
	e = 0;
	tmp = list;
	while (e < (element - 1) && tmp != NULL)
	{
		tmp = tmp->next;
		e++;
	}
	return (e < element && tmp == NULL ? NULL : tmp);
}

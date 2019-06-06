/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addwallinlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:03:41 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/05 17:04:06 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	addwallinlist(t_list **list, t_wall wa)
{
	if (list == NULL)
		*list = ft_lstnew((void*)&wa, sizeof(t_wall));
	else
		ft_lstadd(list, ft_lstnew((void*)&wa, sizeof(t_wall)));
}

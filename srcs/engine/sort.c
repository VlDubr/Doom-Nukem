/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:59:11 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/05 18:18:05 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wallswap(t_list *list, t_ivector cord)
{
	t_wall		*ltmp;
	t_wall		*ltmp1;
	t_fvector2d	z;

	ltmp = (t_wall*)getlistindex(list, cord.x)->content;
	ltmp1 = (t_wall*)getlistindex(list, cord.y)->content;
	z.x = (ltmp->p[0].z + ltmp->p[1].z + ltmp->p[2].z +
	ltmp->p[3].z) / 4.0f;
	z.y = (ltmp1->p[0].z + ltmp1->p[1].z + ltmp1->p[2].z +
	ltmp1->p[3].z) / 4.0f;
	if (z.x < z.y)
		ft_swap(&getlistindex(list, cord.x)->content,
		&getlistindex(list, cord.y)->content);
}

void	drawsort(t_list *list)
{
	size_t		len;
	t_ivector	cord;
	t_wall		tmp;
	t_fvector2d	z;

	len = ft_lstsize(&list);
	cord.z = len / 2;
	while (cord.z > 0)
	{
		cord.y = cord.z;
		while (cord.y < len)
		{
			cord.x = 0;
			while (cord.x < cord.y)
			{
				wallswap(list, cord);
				cord.x++;
			}
			cord.y++;
		}
		cord.z /= 2;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamescene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:50:43 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:08:59 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		*initvisit(size_t size)
{
	size_t	i;
	int		*res;

	if ((res = (int*)ft_memalloc(sizeof(int) * size)) == NULL)
		error("Error: visit not allocated");
	i = 0;
	while (i < size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

void			gamescene(t_doom *doom)
{
	doom->mouseactive = 0;
	update(doom, doom->delta);
	doom->visit = initvisit(doom->thismap.sectorcount);
	doom->portalvisit = initvisit(doom->thismap.sectorcount);
	draw(doom);
	ft_memdel((void**)&doom->visit);
	ft_memdel((void**)&doom->portalvisit);
}

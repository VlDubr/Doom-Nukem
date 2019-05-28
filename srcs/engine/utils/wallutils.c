/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:20:16 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/28 15:20:53 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initdrawwall(t_fvector *view)
{
	int			y;

	y = 0;
	while (y < 4)
	{
		view[y].x = 0;
		view[y].y = 0;
		view[y].z = 0;
		view[y].w = 1;
		y++;
	}
}

void	multmatrixdrawwall(t_fvector *view, t_mat4x4 mat)
{
	view[0] = multipmatrix(view[0], mat);
	view[1] = multipmatrix(view[1], mat);
	view[2] = multipmatrix(view[2], mat);
	view[3] = multipmatrix(view[3], mat);
}

void	divdrawwall(t_fvector *view, float x, float y, float z)
{
	view[0] = divfvector(view[0], x, y, z);
	view[1] = divfvector(view[1], x, y, z);
	view[2] = divfvector(view[2], x, y, z);
	view[3] = divfvector(view[3], x, y, z);
}

void	adddrawwall(t_fvector *view, float x, float y, float z)
{
	view[0] = addfvector(view[0], x, y, z);
	view[1] = addfvector(view[1], x, y, z);
	view[2] = addfvector(view[2], x, y, z);
	view[3] = addfvector(view[3], x, y, z);
}

void	subdrawwall(t_fvector *view, float x, float y, float z)
{
	view[0] = subfvector(view[0], x, y, z);
	view[1] = subfvector(view[1], x, y, z);
	view[2] = subfvector(view[2], x, y, z);
	view[3] = subfvector(view[3], x, y, z);
}

void	multdrawwall(t_fvector *view, float x, float y, float z)
{
	view[0] = multfvector(view[0], x, y, z);
	view[1] = multfvector(view[1], x, y, z);
	view[2] = multfvector(view[2], x, y, z);
	view[3] = multfvector(view[3], x, y, z);
}

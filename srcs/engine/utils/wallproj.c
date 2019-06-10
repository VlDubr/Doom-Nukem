/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallproj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:19:49 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/07 12:17:08 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wallproj(t_fvector *view, t_mat4x4 proj)
{
	multmatrixdrawwall(view, proj);
	view[0] = divfvector(view[0], view[0].w, view[0].w, view[0].w);
	view[1] = divfvector(view[1], view[1].w, view[1].w, view[1].w);
	view[2] = divfvector(view[2], view[2].w, view[2].w, view[2].w);
	view[3] = divfvector(view[3], view[3].w, view[3].w, view[3].w);
	adddrawwall(view, 1, 1, 0);
	multdrawwall(view, 400, 400, 1);
}
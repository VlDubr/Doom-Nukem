/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastfloor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:24:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/07 12:11:38 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_fvector	raycastfloor(t_fvector2d angle, t_fvector2d yse)
{
	t_fvector	res;
	t_fvector	step;

	step.y = (yse.x - yse.y) / sin(angle.y);
	res.y = yse.y;
	res.z = step.y * cos(angle.y);
	step.z = res.z / cos(angle.x);
	res.x = step.z * sin(angle.x);
	return (res);
}

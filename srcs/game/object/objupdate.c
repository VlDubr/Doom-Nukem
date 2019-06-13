/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objupdate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:10:35 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 17:55:07 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	objswitchtexture(float at, t_object *obj)
{
	if (at < 45 || at > 315)
		obj->texture = obj->texturerigth;
	else if (at > 45 && at < 135)
		obj->texture = obj->textureup;
	else if (at > 135 && at < 225)
		obj->texture = obj->textureleft;
	else if (at > 225 && at < 315)
		obj->texture = obj->texturedown;
	else
		obj->texture = obj->textureup;
}

void	logicobj(t_doom *doom, t_object *obj)
{
	if (obj->typeobject == ENEMY)
	{
		moveenemy(doom, obj, doom->delta);
		if (obj->health <= 0)
			obj->isactive = 0;
	}
	else if (obj->typeobject == USE)
		objpickup(doom->setting.input, &doom->player, obj);
	else if (obj->typeobject == LIGHTMOD)
	{
		obj->sector = isinside(setfvector2d(obj->pos.x,
		obj->pos.z), doom->thismap, obj->sector);
		lightmod(obj, &doom->thismap, doom->setting.input);
	}
	else if (obj->typeobject == USEDOOR)
		opendoor(obj, doom->setting.input, &doom->thismap);
}

void	objectupdate(t_doom *doom)
{
	size_t		c;
	t_fvector2d	dirobj;
	float		at;

	c = 0;
	while (c < doom->thismap.objcount)
	{
		if (doom->thismap.obj[c].isactive)
		{
			dirobj = setfvector2d(doom->thismap.obj[c].pos.x
			- doom->player.pos.x,
			doom->thismap.obj[c].pos.z - doom->player.pos.z);
			at = (int)(radtodeg(atan2(dirobj.y, dirobj.x)) + 360) % 360;
			objswitchtexture(at, &doom->thismap.obj[c]);
			agressionememy(&doom->player, &doom->thismap.obj[c]);
			damageenemy(doom->sound.run, &doom->player,
			&doom->thismap.obj[c], doom->delta);
			logicobj(doom, &doom->thismap.obj[c]);
		}
		c++;
	}
}

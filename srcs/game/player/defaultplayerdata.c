/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaultplayerdata.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:51:31 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/11 17:55:26 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_player	defaultplayerdata(t_doom *doom)
{
	t_player r;

	r.maxhealth = 100;
	r.health = 100;
	r.maxstamina = 100;
	r.stamina = 100;
	r.height = 5;
	r.maxheightjump = 10;
	r.movespeed = 0.1f;
	r.runspeed = 0.3f;
	r.run = 0;
	r.jump = 0;
	r.weapons = doom->weapons;
	r.weaponcount = doom->weaponcount;
	r.thisweapon = &doom->weapons[0];
	r.thisweapon->thisammo = 100;
	return (r);
}

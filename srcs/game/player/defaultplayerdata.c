/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaultplayerdata.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:51:31 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/17 12:27:03 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_player	defaultplayerdata(void)
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
	return (r);
}

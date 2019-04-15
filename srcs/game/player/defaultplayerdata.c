/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaultplayerdata.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:51:31 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 17:53:07 by gdaniel          ###   ########.fr       */
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
	r.movespeed = 1;
	r.runspeed = 5;
	r.state = 0;
	return (r);
}

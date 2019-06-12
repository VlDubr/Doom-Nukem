/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statemenu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:55:36 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:56:01 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		statemainmenu(t_doom *doom)
{
	if (boxcollision(doom->newgame, doom->setting.input.mousepos))
		doom->gamestate = 2;
	if (boxcollision(doom->quit, doom->setting.input.mousepos))
		doom->win->state = 0;
}

void		stategameovermenu(t_doom *doom)
{
	if (boxcollision(doom->gameoverbutton, doom->setting.input.mousepos))
		doom->win->state = 0;
}

void		statedifficultymenu(t_doom *doom)
{
	if (boxcollision(doom->easy, doom->setting.input.mousepos))
	{
		doom->player.damagemult = 1;
		doom->gamestate = 1;
	}
	else if (boxcollision(doom->middle, doom->setting.input.mousepos))
	{
		doom->player.damagemult = 2;
		doom->gamestate = 1;
	}
	else if (boxcollision(doom->hard, doom->setting.input.mousepos))
	{
		doom->player.damagemult = 3;
		doom->gamestate = 1;
	}
}

void		menuupdate(t_doom *doom)
{
	if (doom->setting.input.mousekey[0])
	{
		if (doom->gamestate == 0)
			statemainmenu(doom);
		else if (doom->gamestate == 2)
			statedifficultymenu(doom);
		else if (doom->gamestate == 3)
			stategameovermenu(doom);
	}
}

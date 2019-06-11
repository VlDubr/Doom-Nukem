/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:51:13 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/11 17:59:38 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	drawplayer(uint32_t *p, t_player play, t_ivector2d cord)
{
	t_fvector	dir;

	dir.x = cos(play.rotate.z) * 5;
	dir.y = sin(play.rotate.z) * 5;
	drawline(p, setfvector(cord.x, cord.y, 0, 1),
	setfvector(cord.x + dir.x, cord.y + dir.y, 0, 1), setrgb(255, 255, 0));
}

void	drawenemy(uint32_t *p, t_player play, t_map *map, t_ivector2d cord)
{
	t_fvector	e;
	t_rgb		color;
	size_t		count;

	count = 0;
	while (count < map->objcount)
	{
		if (map->obj[count].isactive && map->obj[count].typeobject != DECORE)
		{
			if (map->obj[count].typeobject == ENEMY)
				color = setrgb(255, 0, 0);
			else if (map->obj[count].typeobject == USE)
				color = setrgb(0, 255, 0);
			else
				color = setrgb(0, 0, 255);
			e = setfvector(map->obj[count].pos.x, map->obj[count].pos.z, 0, 1);
			e = subfvector(e, play.pos.x, play.pos.z, 0);
			e = addfvector(e, cord.x, cord.y, 0);
			if (e.x >= 0 && e.x < 800 && e.y >= 0 && e.y < 800)
				p[(int)e.x + ((int)e.y * 800)] = ((((((255 << 8) |
				color.red) << 8) | color.green) << 8) | color.blue);
		}
		count++;
	}
}

void	drawother(t_doom *doom, t_ivector2d cord)
{
	drawenemy(doom->win->pixels, doom->player, &doom->thismap, cord);
	drawplayer(doom->win->pixels, doom->player, cord);
}

void	drawminimap(uint32_t *p, t_doom *doom, size_t sector, t_ivector2d cord)
{
	t_fvector	p1;
	t_fvector	p2;
	t_fvector	*w;
	size_t		c;
	size_t		i;

	w = doom->thismap.walls;
	c = doom->thismap.sectors[sector].start;
	w = doom->thismap.walls;
	i = -1;
	while (++i < doom->thismap.sectors[sector].count)
	{
		p1 = setfvector(w[c + i].x, w[c + i].y, 0, 1);
		p2 = setfvector(w[c + i + 1 >=
		c + doom->thismap.sectors[sector].count ? c : c + i + 1].x,
		w[c + i + 1 >= c + doom->thismap.sectors[sector].count ?
		c : c + i + 1].y, 0, 1);
		p1 = subfvector(p1, doom->player.pos.x, doom->player.pos.z, 0);
		p2 = subfvector(p2, doom->player.pos.x, doom->player.pos.z, 0);
		p1 = addfvector(p1, cord.x, cord.y, 0);
		p2 = addfvector(p2, cord.x, cord.y, 0);
		w[c + i].z == -1 ? drawline(p, p1, p2, setrgb(255, 255, 255)) :
		drawline(p, p1, p2, setrgb(255, 0, 0));
	}
	drawother(doom, cord);
}

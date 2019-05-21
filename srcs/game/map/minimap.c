/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:51:13 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/21 13:13:37 by gdaniel          ###   ########.fr       */
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

	// t_fvector2d ray1;
	// ray1.x = cos(play.rotate.z + 1.57) * 100;
	// ray1.y = sin(play.rotate.z + 1.57) * 100;
	// drawline(p, setfvector(cord.x, cord.y, 0, 1),
	// setfvector(cord.x + ray1.x, cord.y + ray1.y, 0, 1), setrgb(0, 0, 255));
	// ray1.x = cos(play.rotate.z - 1.57) * 100;
	// ray1.y = sin(play.rotate.z - 1.57) * 100;
	// drawline(p, setfvector(cord.x, cord.y, 0, 1),
	// setfvector(cord.x + ray1.x, cord.y + ray1.y, 0, 1), setrgb(0, 0, 255));
}

void	drawenemy(uint32_t *p, t_player play, t_map *map, t_ivector2d cord)
{
	t_fvector	e;
	t_rgb		color;
	size_t		count;

	count = 0;
	color = setrgb(255, 0, 0);
	while (count < map->objcount)
	{
		e = setfvector(map->obj[count].pos.x, map->obj[count].pos.z, 0, 1);
		e = subfvector(e, play.pos.x, play.pos.z, 0);
		e = addfvector(e, cord.x, cord.y, 0);
		if (e.x >= 0 && e.x < 800 && e.y >= 0 && e.y < 800)
			p[(int)e.x + ((int)e.y * 800)] = ((((((255 << 8) | color.red) << 8) | color.green) << 8) | color.blue);
		count++;
	}
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
	drawenemy(p, doom->player, &doom->thismap, cord);
	drawplayer(p, doom->player, cord);

	// c = doom->thismap.sectors[sector].start;
	// i = -1;
	// t_wall wa;
	// t_fvector2d min;
	// t_fvector2d max;
	// t_rgb	color;
	// min = setfvector2d(w[0].x, w[0].y);
	// max = setfvector2d(w[0].x, w[0].y);
	// while (++i < doom->thismap.sectors[sector].count)
	// {
	// 	min.x = ft_fmin(min.x, w[c + i].x);
	// 	min.y = ft_fmin(min.y, w[c + i].y);
	// 	max.x = ft_fmax(max.x, w[c + i].x);
	// 	max.y = ft_fmax(max.y, w[c + i].y);
	// }
	// wa.p[0] = subfvector(setfvector(min.x, min.y, 0, 1), doom->player.pos.x, doom->player.pos.z, 0);
	// wa.p[1] = subfvector(setfvector(min.x, max.y, 0, 1), doom->player.pos.x, doom->player.pos.z, 0);
	// wa.p[2] = subfvector(setfvector(max.x, max.y, 0, 1), doom->player.pos.x, doom->player.pos.z, 0);
	// wa.p[3] = subfvector(setfvector(max.x, min.y, 0, 1), doom->player.pos.x, doom->player.pos.z, 0);

	// wa.p[0] = addfvector(wa.p[0], 400, 300, 0);
	// wa.p[1] = addfvector(wa.p[1], 400, 300, 0);
	// wa.p[2] = addfvector(wa.p[2], 400, 300, 0);
	// wa.p[3] = addfvector(wa.p[3], 400, 300, 0);
	// color = setrgb(255, 255, 255);
	// drawline(p, wa.p[0], wa.p[1], color);
	// drawline(p, wa.p[1], wa.p[2], color);
	// drawline(p, wa.p[2], wa.p[3], color);
	// drawline(p, wa.p[3], wa.p[0], color);
}

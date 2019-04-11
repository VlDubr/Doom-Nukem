/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:38:06 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/11 18:33:23 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map		testmap(void)
{
	t_map	r;

	r.wallcount = 15;
	r.walls = (t_fvector*)malloc(sizeof(t_fvector) * r.wallcount);
	r.walls[0] = setfvector(0, 0, -1);
	r.walls[1] = setfvector(50, 0, -1);
	r.walls[2] = setfvector(75, 25, 1);
	r.walls[3] = setfvector(50, 50, -1);
	r.walls[4] = setfvector(0, 50, -1);
	r.walls[5] = setfvector(-25, 25, -1);

	r.walls[6] = setfvector(75, 25, 0);
	r.walls[7] = setfvector(50, 50, -1);
	r.walls[8] = setfvector(84, 50, 2);
	r.walls[9] = setfvector(100, 50, -1);
	r.walls[10] = setfvector(100, 25, -1);

	r.walls[11] = setfvector(84, 50, -1);
	r.walls[12] = setfvector(84, 100, -1);
	r.walls[13] = setfvector(100, 100, -1);
	r.walls[14] = setfvector(100, 50, 1);


	r.sectorcount = 3;
	r.sectors = (t_sector*)malloc(sizeof(t_sector) * r.sectorcount);

	r.sectors[0].start = 0;
	r.sectors[0].count = 6;
	r.sectors[0].floor = 1;
	r.sectors[0].height = 10;


	r.sectors[1].start = 6;
	r.sectors[1].count = 5;
	r.sectors[1].floor = 5;
	r.sectors[1].height = 10;

	r.sectors[2].start = 11;
	r.sectors[2].count = 4;
	r.sectors[2].floor = 1;
	r.sectors[2].height = 10;

	r.startplayer.sector = 0;
	r.startplayer.pos = setfvector(10, 0, 10);
	r.startplayer.rotate = setfvector(0, 0, 0);

	return (r);
}

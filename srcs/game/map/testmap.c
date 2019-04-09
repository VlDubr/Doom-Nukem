/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:38:06 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 13:05:02 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map		testmap(void)
{
	t_map	r;

	r.wallcount = 11;
	r.walls = (t_fvector2d*)malloc(sizeof(t_fvector2d) * r.wallcount);
	r.walls[0] = setfvector2d(0, 0);
	r.walls[1] = setfvector2d(50, 0);
	r.walls[2] = setfvector2d(75, 25);
	r.walls[3] = setfvector2d(-25, 25);
	r.walls[4] = setfvector2d(100, 25);
	r.walls[5] = setfvector2d(50, 50);
	r.walls[6] = setfvector2d(0, 50);
	r.walls[7] = setfvector2d(84, 50);
	r.walls[8] = setfvector2d(100, 50);
	r.walls[9] = setfvector2d(84, 100);
	r.walls[10] = setfvector2d(100, 100);

	r.sectorcount = 3;
	r.sectors = (t_sector*)malloc(sizeof(t_sector) * r.sectorcount);

	r.sectors[0].wallcount = 6;
	r.sectors[0].walls = (t_wall*)malloc(sizeof(t_wall)
	* r.sectors[0].wallcount);
	r.sectors[0].floor = 1;
	r.sectors[0].height = 10;

	r.sectors[0].walls[0].sp = 0;
	r.sectors[0].walls[0].ep = 1;
	r.sectors[0].walls[0].nextsector = -1;

	r.sectors[0].walls[1].sp = 1;
	r.sectors[0].walls[1].ep = 2;
	r.sectors[0].walls[1].nextsector = -1;

	r.sectors[0].walls[2].sp = 2;
	r.sectors[0].walls[2].ep = 5;
	r.sectors[0].walls[2].nextsector = 1;

	r.sectors[0].walls[3].sp = 5;
	r.sectors[0].walls[3].ep = 6;
	r.sectors[0].walls[3].nextsector = -1;

	r.sectors[0].walls[4].sp = 6;
	r.sectors[0].walls[4].ep = 3;
	r.sectors[0].walls[4].nextsector = -1;

	r.sectors[0].walls[5].sp = 3;
	r.sectors[0].walls[5].ep = 0;
	r.sectors[0].walls[5].nextsector = -1;

	r.sectors[1].wallcount = 5;
	r.sectors[1].walls = (t_wall*)malloc(sizeof(t_wall)
	* r.sectors[1].wallcount);
	r.sectors[1].floor = 5;
	r.sectors[1].height = 10;

	r.sectors[1].walls[0].sp = 2;
	r.sectors[1].walls[0].ep = 5;
	r.sectors[1].walls[0].nextsector = 0;

	r.sectors[1].walls[1].sp = 5;
	r.sectors[1].walls[1].ep = 7;
	r.sectors[1].walls[1].nextsector = -1;

	r.sectors[1].walls[2].sp = 7;
	r.sectors[1].walls[2].ep = 8;
	r.sectors[1].walls[2].nextsector = 2;

	r.sectors[1].walls[3].sp = 8;
	r.sectors[1].walls[3].ep = 4;
	r.sectors[1].walls[3].nextsector = -1;

	r.sectors[1].walls[4].sp = 4;
	r.sectors[1].walls[4].ep = 2;
	r.sectors[1].walls[4].nextsector = -1;

	r.sectors[2].wallcount = 4;
	r.sectors[2].walls = (t_wall*)malloc(sizeof(t_wall)
	* r.sectors[2].wallcount);
	r.sectors[2].floor = 1;
	r.sectors[2].height = 10;

	r.sectors[2].walls[0].sp = 7;
	r.sectors[2].walls[0].ep = 8;
	r.sectors[2].walls[0].nextsector = 1;

	r.sectors[2].walls[1].sp = 8;
	r.sectors[2].walls[1].ep = 10;
	r.sectors[2].walls[1].nextsector = -1;

	r.sectors[2].walls[2].sp = 10;
	r.sectors[2].walls[2].ep = 9;
	r.sectors[2].walls[2].nextsector = -1;

	r.sectors[2].walls[3].sp = 9;
	r.sectors[2].walls[3].ep = 7;
	r.sectors[2].walls[3].nextsector = -1;

	r.startplayer.startsector = 1;
	r.startplayer.pos = setfvector(64.028748, r.sectors[r.startplayer.startsector].floor + 5, 39.596561);
	r.startplayer.rotate = setfvector(0, -1.749999, 0);

	return (r);
}

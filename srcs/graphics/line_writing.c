/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_writing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:24:36 by srafe             #+#    #+#             */
/*   Updated: 2019/06/05 16:10:25 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

static void	line_put(double xy[5], t_sdl *sdl)
{
	int i;

	i = 0;
	while (i++ <= xy[4] - 2)
	{
		xy[0] += xy[2];
		xy[1] += xy[3];
		if ((xy[0] > 1100 || xy[1] > 1100) || (xy[0] < -800 || xy[1] < -800))
			return ;
		SDL_RenderDrawPoint(sdl->r, roundf(xy[0]), roundf(xy[1]));
	}
}

void		line_dda(t_wall start, t_wall finish, t_sdl *sdl, t_serv *s)
{
	int		rc[4];
	double	xy[5];

	rc[0] = roundf(start.xy[0]);
	rc[1] = roundf(start.xy[1]);
	rc[2] = roundf(finish.xy[0]);
	rc[3] = roundf(finish.xy[1]);
	xy[4] = ft_max(abs(rc[0] - rc[2]), abs(rc[1] - rc[3])) + 1;
	if (xy[4] == 1)
	{
		SDL_RenderDrawPoint(sdl->r, start.xy[0], start.xy[1]);
		return ;
	}
	xy[2] = (finish.xy[0] - start.xy[0]) / (xy[4] - 1);
	xy[3] = (finish.xy[1] - start.xy[1]) / (xy[4] - 1);
	xy[0] = start.xy[0] + (s->wh_screen[0] / 2) + s->coord_x;
	xy[1] = start.xy[1] + (s->wh_screen[1] / 2) + s->coord_y;
	line_put(xy, sdl);
}

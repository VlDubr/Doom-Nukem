/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:02:57 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 18:50:24 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	writer(t_serv *s, t_sdl sdl, t_map *map)
{
	SDL_RenderClear(sdl.r);
	background(&sdl);
	gui(s, &sdl, map);
	map_writer(&sdl, s, map);
	if (s->p_flag == 1)
		pl_write(s, sdl);
	dot_write(s, &sdl, map);
	tex_write(s, sdl, map);
	obj_writer(s, sdl, map);
	SDL_RenderPresent(sdl.r);
}

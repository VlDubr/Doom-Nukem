/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:09:19 by srafe             #+#    #+#             */
/*   Updated: 2019/04/11 17:57:06 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	t_tga		*img;
	int			x;
	int			y;
	SDL_Event	e;
	int			quit;

	SDL_Init(SDL_INIT_EVERYTHING);
	if (argc == 2)
		img = tga_reader(argv[1]);

	sdl.win = SDL_CreateWindow("TGA Reader", 0, 0, img->width, img->height, 0);
	sdl.ren = SDL_CreateRenderer(sdl.win, -1, 0);
	SDL_RenderClear(sdl.ren);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			SDL_SetRenderDrawColor(sdl.ren, img->pic[y][x].red, img->pic[y][x].green, img->pic[y][x].blue, img->pic[y][x].alpha);
			SDL_RenderDrawPoint(sdl.ren, x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(sdl.ren);
	SDL_RenderClear(sdl.ren);
	quit = 0;

	while (quit == 0)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			if (e.type == SDLK_ESCAPE)
				quit = 1;
		}
	}

	return (0);
}

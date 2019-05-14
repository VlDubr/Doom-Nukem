/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/14 16:21:35 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/editor.h"

int main (int argc, char **argv)
{
    t_sdl		sdl;
    SDL_Event	e;
    int quit;
    int fd;

    SDL_Init(SDL_INIT_EVERYTHING);
    sdl.win = SDL_CreateWindow("TGA Reader", 0, 0, 200, 200, 0);
	sdl.ren = SDL_CreateRenderer(sdl.win, -1, 0);
	SDL_RenderClear(sdl.ren);

	editor("file.txt");

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
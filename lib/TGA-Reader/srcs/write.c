/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:23:46 by srafe             #+#    #+#             */
/*   Updated: 2019/05/27 18:31:28 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

static void	draw_text(t_tga **img, SDL_Renderer *r, t_ivector2d wh, int nixy[4])
{
	SDL_SetRenderDrawColor(r, img[nixy[0]]->pic[nixy[3]][nixy[2]].red,
							img[nixy[0]]->pic[nixy[3]][nixy[2]].green,
							img[nixy[0]]->pic[nixy[3]][nixy[2]].blue,
							img[nixy[0]]->pic[nixy[3]][nixy[2]].alpha);
	SDL_RenderDrawPoint(r,
	wh.x + nixy[2] + (img[nixy[0]]->width * (nixy[1] + 1)), nixy[3] + wh.y);
}

void	bitmap_write(SDL_Renderer *r, t_tga **img, t_ivector2d wh, char *str)
{
	int	nixy[4];

	nixy[1] = 0;
	while (str[nixy[1]] != '\0')
	{
		nixy[0] = (int)(str[nixy[1]] - 32);
		nixy[3] = 0;
		while (nixy[3] < img[nixy[0]]->height)
		{
			nixy[2] = 0;
			while (nixy[2] < img[nixy[0]]->width)
			{
				if (img[nixy[0]]->pic[nixy[3]][nixy[2]].red != 0
				|| img[nixy[0]]->pic[nixy[3]][nixy[2]].green != 0
				|| img[nixy[0]]->pic[nixy[3]][nixy[2]].blue != 0)
					draw_text(img, r, wh, nixy);
				nixy[2]++;
			}
			nixy[3]++;
		}
		nixy[1]++;
	}
}

static void	draw_img(t_tga *img, SDL_Renderer *r, t_ivector2d wh, int *xy)
{
	SDL_SetRenderDrawColor(r, img->pic[xy[1]][xy[0]].red,
							img->pic[xy[1]][xy[0]].green,
							img->pic[xy[1]][xy[0]].blue,
							img->pic[xy[1]][xy[0]].alpha);
	SDL_RenderDrawPoint(r, xy[0] + wh.x, xy[1] + wh.y);
}

void	img_write(SDL_Renderer *r, t_tga *img, t_ivector2d wh)
{
	int	xy[2];

	xy[1] = 0;
	while (xy[1] < img->height)
	{
		xy[0] = 0;
		while (xy[0] < img->width)
		{
			if (img->pic[xy[1]][xy[0]].red != 0
				|| img->pic[xy[1]][xy[0]].green != 0
				|| img->pic[xy[1]][xy[0]].blue != 0)
				draw_img(img, r, wh, xy);
			xy[0]++;
		}
		xy[1]++;
	}
}

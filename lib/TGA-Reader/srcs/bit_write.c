/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:23:46 by srafe             #+#    #+#             */
/*   Updated: 2019/04/18 17:49:07 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

void		bitmap_write(SDL_Renderer *r, t_tga	**img, t_ivector2d wh, char *str)
{
	int	i;
	int	x;
	int	y;
	int	num;

	i = 0;
	while (str[i] != '\0')
	{
		num =  (int)(str[i] - 32);
		y = 0;
		while (y < img[num]->height)
		{
			x = 0;
			while (x < img[num]->width)
			{
				SDL_SetRenderDrawColor(r, img[num]->pic[y][x].red, img[num]->pic[y][x].green,
					img[num]->pic[y][x].blue, img[num]->pic[y][x].alpha);
				SDL_RenderDrawPoint(r, x + (wh.x * (i + 1)), y + wh.y);
				x++;
			}
			y++;
		}
		i++;
	}
}
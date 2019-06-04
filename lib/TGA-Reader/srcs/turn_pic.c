/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:37:09 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 19:05:50 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

void	turn_pic_g(t_tga *img)
{
	int		x;
	int		y;
	t_rgba	temp;

	y = 0;
	while (y < img->height / 2)
	{
		x = 0;
		while (x < img->width)
		{
			temp = img->pic[y][x];
			img->pic[y][x] = img->pic[img->height - y - 1][x];
			img->pic[img->height - y - 1][x] = temp;
			x++;
		}
		y++;
	}
}

void	turn_pic_v(t_tga *img)
{
	int		x;
	int		y;
	t_rgba	temp;

	x = 0;
	while (x < img->width / 2)
	{
		y = 0;
		while (y < img->height)
		{
			temp = img->pic[y][x];
			img->pic[y][x] = img->pic[y][img->height - x - 1];
			img->pic[y][img->height - x - 1] = temp;
			y++;
		}
		x++;
	}
}

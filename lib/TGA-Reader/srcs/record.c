/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:19:22 by srafe             #+#    #+#             */
/*   Updated: 2019/04/17 15:29:29 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

static void	rgba(t_tga *img, unsigned char *buf, t_service *s, int k)
{
	img->pic[s->y][s->x].blue = buf[k];
	img->pic[s->y][s->x].green = buf[k + 1];
	img->pic[s->y][s->x].red = buf[k + 2];
	if (img->bpp == 32)
		img->pic[s->y][s->x].alpha = buf[k + 3];
	else
		img->pic[s->y][s->x].alpha = 255;
}

void		rec(t_tga *img, unsigned char *buf, t_service *s)
{
	unsigned int	k;
	int				step;

	k = 0;
	step = img->bpp / 8;
	while (k < s->read_l && s->y < img->height)
	{
		while (k < s->read_l && s->x < img->width)
		{
			rgba(img, buf, s, k);
			s->x++;
			k += step;
		}
		if (s->x >= img->width)
		{
			s->x = 0;
			s->y++;
		}
	}
}

static void	fckng_nrm(t_tga *img, t_service *s, unsigned char *buf, int k)
{
	rgba(img, buf, s, k);
	s->i++;
	s->x++;
	if (s->x >= img->width)
	{
		s->x = 0;
		s->y++;
	}
}

void		c_rec(t_tga *img, unsigned char *buf, t_service *s)
{
	unsigned int	k;
	int				chunkheader;

	k = 0;
	while (k < s->read_l)
	{
		s->i = 0;
		if ((chunkheader = buf[k]) >= 128)
		{
			chunkheader -= 127;
			while (s->i < chunkheader && s->y < img->height)
				fckng_nrm(img, s, buf, k + 1);
			k += img->bpp / 8 + 1;
		}
		else
		{
			k++;
			while (k < s->read_l && s->i <= chunkheader && s->y < img->height)
			{
				fckng_nrm(img, s, buf, k);
				k += img->bpp / 8;
			}
		}
	}
}

void		mono_rec(t_tga *img, unsigned char *buf, t_service *s)
{
	unsigned int	k;

	k = 0;
	while (k < s->read_l && s->y < img->height)
	{
		while (k < s->read_l && s->x < img->width)
		{
			img->pic[s->y][s->x].blue = buf[k];
			img->pic[s->y][s->x].green = buf[k];
			img->pic[s->y][s->x].red = buf[k];
			img->pic[s->y][s->x].alpha = 255;
			s->x++;
			k++;
		}
		if (s->x >= img->width)
		{
			s->x = 0;
			s->y++;
		}
	}
}

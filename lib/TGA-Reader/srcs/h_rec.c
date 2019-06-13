/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_rec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:10:45 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 14:46:40 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

void		head_rec(t_tga *img, unsigned char *buf, t_service *s)
{
	img->id_length = buf[0];
	if ((img->color_map = buf[1]) != 0)
		ft_error("I do not read pictures with a color map!");
	img->data_type = buf[2];
	if (img->data_type != 10 && img->data_type != 2
		&& img->data_type != 3)
		ft_error("Wrong data type!");
	img->xy_origin[0] = (buf[9] << 8) | buf[8];
	img->xy_origin[1] = (buf[11] << 8) | buf[10];
	img->width = (buf[13] << 8) | buf[12];
	img->height = (buf[15] << 8) | buf[14];
	img->bpp = buf[16];
	if (img->bpp != 24 && img->bpp != 32 && img->bpp != 8)
		ft_error("Damaged file (wrong bpp)!");
	img->flip_g = buf[17] & 32;
	img->flip_v = buf[17] & 16;
	s->read_l = img->width * img->height * (img->bpp / 8);
}

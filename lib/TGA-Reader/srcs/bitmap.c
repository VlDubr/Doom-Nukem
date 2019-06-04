/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:23:09 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 19:06:52 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

static void	trim(t_tga **images, t_tga *img, int numb, t_ivector2d wh)
{
	t_service	s;

	s.xx = 0;
	s.yy = 0;
	s.i = 0;
	while (s.i < numb && (s.yy <= (img->height - wh.y)))
	{
		s.y = 0;
		while (s.y < wh.y)
		{
			s.x = -1;
			while (++s.x < wh.x)
				images[s.i]->pic[s.y][s.x] = img->pic[s.y + s.yy][s.x + s.xx];
			s.y++;
		}
		s.xx += wh.x;
		if (s.xx >= (img->width - wh.x))
		{
			s.xx = 0;
			s.yy += wh.y;
		}
		s.i++;
	}
}

t_tga		**images_mall(t_tga *img, int numb, t_ivector2d wh)
{
	int		i;
	t_tga	**images;

	images = (t_tga **)malloc(sizeof(t_tga *) * numb);
	i = 0;
	while (i < numb)
	{
		images[i] = (t_tga *)malloc(sizeof(t_tga));
		if (!(images[i]->pic = malloc_pic(images[i]->pic, wh.x, wh.y)))
			ft_error("Malloc error!");
		images[i]->width = wh.x;
		images[i]->height = wh.y;
		images[i]->data_type = img->data_type;
		images[i]->bpp = img->bpp;
		images[i]->id_length = 0;
		images[i]->flip_g = 0;
		images[i]->flip_v = 0;
		i++;
	}
	return (images);
}

t_tga		**bitmap(char *path, t_ivector2d wh)
{
	t_tga	*img;
	t_tga	**images;
	int		numb;

	img = tga_reader(path);
	numb = ((img->height * img->width) / (wh.x * wh.y));
	images = images_mall(img, numb, wh);
	trim(images, img, numb, wh);
	free_pic(img);
	free(img);
	return (images);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:28:14 by srafe             #+#    #+#             */
/*   Updated: 2019/04/17 15:29:11 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

static void	turn_pix_g(t_tga *img)
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

static void	turn_pix_v(t_tga *img)
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

static void	recorder(t_tga *img, unsigned char *buf, t_service *s)
{
	if (img->data_type == 2)
		rec(img, buf, s);
	else if (img->data_type == 3)
		mono_rec(img, buf, s);
	else if (img->data_type == 10)
		c_rec(img, buf, s);
}

static void	first_step(t_tga *img, unsigned char *buf, t_service *s, int fd)
{
	unsigned char	*del;

	head_rec(img, buf, s);
	if (img->id_length != 0)
		read(fd, buf, img->id_length);
	del = buf;
	free(del);
}

static t_tga	*reader(int fd, t_service *s)
{
	unsigned char	*buf;
	t_tga			*img;

	img = (t_tga *)malloc(sizeof(t_tga));
	buf = (unsigned char *)malloc(sizeof(char) * 1000);
	while ((s->j = read(fd, buf, s->read_l)) > 0)
	{
		buf[s->j] = '\0';
		if (s->j == 18)
		{
			first_step(img, buf, s, fd);
			if (!(img->pic = malloc_pic(img->pic, img->width, img->height)))
				ft_error("Malloc error!");
			buf = (unsigned char *)malloc(sizeof(char) * (s->read_l + 1));
		}
		else
			recorder(img, buf, s);
	}
	if (s->j == -1)
		ft_error("Read file error");
	free(buf);
	return (img);
}

t_tga		*tga_reader(char *path)
{
	int			fd;
	t_service	s;
	t_tga		*img;

	s.x = 0;
	s.y = 0;
	s.read_l = 18;
	img = NULL;
	if ((fd = open(path, O_RDWR)) > 0)
		img = reader(fd, &s);
	else if (fd == -1)
		ft_error("Wrong file path");
	close(fd);
	if (img->flip_g == 0)
		turn_pix_g(img);
	if (img->flip_v == 1)
		turn_pix_v(img);
	return (img);
}

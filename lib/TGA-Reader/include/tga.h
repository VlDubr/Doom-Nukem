/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:11:21 by srafe             #+#    #+#             */
/*   Updated: 2019/04/17 20:08:01 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../../ft_graphics/includes/color.h"
# include "../../libft/includes/libft.h"


typedef struct		s_service
{
	int				j;
	int				x;
	int				y;
	int				i;
	unsigned int	read_l;
	int				flag;
}					t_service;

typedef struct		s_tga
{
	t_rgba			**pic;
	unsigned char	id_length;
	unsigned char	color_map;
	unsigned char	data_type;
	unsigned char	xy_origin[2];
	short int		width;
	short int		height;
	unsigned char	bpp;
	unsigned char	flip_g;
	unsigned char	flip_v;
}					t_tga;

t_rgba				**malloc_pic(t_rgba **pix, int width, int height);
t_tga				*tga_reader(char *path);

void				ft_error(const char *str);
void				head_rec(t_tga *img, unsigned char buf[], t_service *s);
void				rec(t_tga *img, unsigned char buf[], t_service *s);
void				c_rec(t_tga *img, unsigned char buf[], t_service *s);
void				mono_rec(t_tga *img, unsigned char *buf, t_service *s);
#endif

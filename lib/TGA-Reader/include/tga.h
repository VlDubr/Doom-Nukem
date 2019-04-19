/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:11:21 by srafe             #+#    #+#             */
/*   Updated: 2019/04/18 15:16:30 by vmcclure         ###   ########.fr       */
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
	int				i;
	int				j;
	int				x;
	int				y;
	int				xx;
	int				yy;
	long			read_l;
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
void 				free_pic(t_tga *img);

t_tga				**bitmap(char *path, t_ivector2d wh);
t_tga				*tga_reader(char *path);

void				head_rec(t_tga *img, unsigned char buf[], t_service *s);
void				rec(t_tga *img, unsigned char buf[], t_service *s);
void				c_rec(t_tga *img, unsigned char buf[], t_service *s);
void				mono_rec(t_tga *img, unsigned char *buf, t_service *s);
void				ft_error(const char *str);
void				turn_pic_g(t_tga *img);
void				turn_pic_v(t_tga *img);
#endif

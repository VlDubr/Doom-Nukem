/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:11:21 by srafe             #+#    #+#             */
/*   Updated: 2019/05/31 16:10:29 by gdaniel          ###   ########.fr       */
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

# ifdef __APPLE__
#  define CREATEFLAG S_IWRITE | S_IREAD
#  include "../../SDL/include/SDL2/SDL.h"
# elif __linux__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <SDL2/SDL.h>
# elif __WIN32__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL.h>

# endif

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
void				free_pic(t_tga *img);

void				bitmap_write(SDL_Renderer *r,
					t_tga	**images, t_ivector2d wh, char *str);
t_tga				**bitmap_mall(t_tga *img, t_ivector2d wh, int *count);
void				img_write(SDL_Renderer *r, t_tga *img, t_ivector2d wh);

t_tga				**bitmap(char *path, t_ivector2d wh);
t_tga				*tga_reader(char *path);

void				head_rec(t_tga *img, unsigned char buf[], t_service *s);
void				rec(t_tga *img, unsigned char buf[], t_service *s);
void				c_rec(t_tga *img, unsigned char buf[], t_service *s);
void				mono_rec(t_tga *img, unsigned char *buf, t_service *s);

void				turn_pic_g(t_tga *img);
void				turn_pic_v(t_tga *img);

void				ft_error(const char *str);
#endif

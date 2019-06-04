/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:24:19 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 19:05:42 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

t_rgba	**malloc_pic(t_rgba **pic, int width, int height)
{
	int	i;

	if (!(pic = (t_rgba **)malloc(sizeof(t_rgba *) * height)))
		ft_error("Malloc error!");
	i = 0;
	while (i < height)
	{
		if (!(pic[i] = (t_rgba *)malloc(sizeof(t_rgba) * width)))
			ft_error("Malloc error!");
		i++;
	}
	return (pic);
}

void	free_pic(t_tga *img)
{
	int	i;

	i = 0;
	while (i < img->height)
	{
		free(img->pic[i]);
		i++;
	}
	free(img->pic);
}

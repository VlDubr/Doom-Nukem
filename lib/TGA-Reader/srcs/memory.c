/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:24:19 by srafe             #+#    #+#             */
/*   Updated: 2019/04/17 15:41:33 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

t_rgba	**malloc_pic(t_rgba **pix, int width, int height)
{
	int	i;

	if (!(pix = (t_rgba**)malloc(sizeof(t_rgba *) * (height + 100))))
		ft_error("Malloc error!");
	i = 0;
	while (i < width)
	{
		if (!(pix[i] = (t_rgba *)malloc(sizeof(t_rgba) * (width + 100))))
			ft_error("Malloc error!");
		i++;
	}
	return (pix);
}

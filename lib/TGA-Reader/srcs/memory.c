/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:24:19 by srafe             #+#    #+#             */
/*   Updated: 2019/04/11 18:15:18 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

t_rgba	**malloc_pix(t_rgba **pix, int width, int height)
{
	int	i;

	if (!(pix = (t_rgba**)malloc(sizeof(t_rgba*) * height)))
		return (0);
	i = 0;
	while (i < width)
	{
		if (!(pix[i] = (t_rgba*)malloc(sizeof(t_rgba) * width)))
			return (0);
		i++;
	}
	return (pix);
}

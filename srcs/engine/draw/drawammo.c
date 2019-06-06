/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawammo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:13:12 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/31 18:11:15 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	font_write(uint32_t *p, t_tga **font, t_ivector2d wh, char *str)
{
	int		nixy[4];
	t_rgba	*color;

	nixy[1] = 0;
	while (str[nixy[1]] != '\0')
	{
		nixy[0] = (int)(str[nixy[1]] - 32);
		nixy[3] = 0;
		while (nixy[3] < font[nixy[0]]->height)
		{
			nixy[2] = 0;
			while (nixy[2] < font[nixy[0]]->width)
			{
				color = &font[nixy[0]]->pic[nixy[3]][nixy[2]];
				if (font[nixy[0]]->pic[nixy[3]][nixy[2]].alpha != 0)
					drawpoint(p, setivector2d(800, 800), setivector2d(wh.x
					+ nixy[2] + (font[nixy[0]]->width * (nixy[1] + 1)),
					nixy[3] + wh.y), *color);
				nixy[2]++;
			}
			nixy[3]++;
		}
		nixy[1]++;
	}
}

void	drawammo(t_doom *doom)
{
	char *ammostring;

	ammostring = ft_itoa(doom->player.thisweapon->thisammo);
	font_write(doom->win->pixels, doom->font,
	setivector2d(0, 740), ammostring);
	ft_strdel(&ammostring);
}

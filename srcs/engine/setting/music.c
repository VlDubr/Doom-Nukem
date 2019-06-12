/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:22:05 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:06:00 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	addmusic(t_setting *s)
{
	if (s->musicvolume + 1 < 129)
		s->musicvolume += 1;
}

void	submusic(t_setting *s)
{
	if (s->musicvolume - 1 > -1)
		s->musicvolume -= 1;
}

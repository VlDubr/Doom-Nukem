/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:20:35 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:06:35 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	addsound(t_setting *s)
{
	if (s->soundvolume + 1 < 129)
		s->soundvolume += 1;
}

void	subsound(t_setting *s)
{
	if (s->soundvolume - 1 > -1)
		s->soundvolume -= 1;
}

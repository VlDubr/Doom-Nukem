/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initsetting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:16:40 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/28 13:17:41 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initsetting(t_setting *s)
{
	s->soundvolume = 0;
	s->musicvolume = 0;
	s->resolution = setivector2d(800, 800);
}

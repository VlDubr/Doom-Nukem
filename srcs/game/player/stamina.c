/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stamina.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:37:25 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/17 12:38:25 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	addstamina(t_player *p, float addvalue)
{
	if (p->stamina < p->maxstamina)
		p->stamina += addvalue;
}

void	minusstamina(t_player *p, float minusvalue)
{
	if (p->stamina > 0)
		p->stamina -= minusvalue;
}

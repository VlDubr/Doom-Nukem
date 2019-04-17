/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:36:01 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/17 12:39:20 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	addhealth(t_player *p, float addvalue)
{
	if (p->health < p->maxhealth)
		p->health += addvalue;
}

void	minushealth(t_player *p, float minusvalue)
{
	if (p->health > 0)
		p->health -= minusvalue;
}

void	playerdeath(t_player *p)
{
	if (p->health <= 0)
		printf("Death\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boxcollide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:17:20 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:17:35 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	boxcollision(t_button button, t_ivector2d mousepos)
{
	if (mousepos.x > button.rect.start.x &&
	mousepos.y > button.rect.start.y &&
	mousepos.x < button.rect.start.x + button.rect.width &&
	mousepos.y < button.rect.start.y + button.rect.height)
		return (1);
	return (0);
}
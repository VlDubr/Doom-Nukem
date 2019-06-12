/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initsettingui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:02:13 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 10:15:49 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initsettingui(t_doom *doom)
{
	doom->settingui.plussound.rect = setirect(setivector2d(50, 50), 50, 50);
	//doom->settingui.plussound.texture = doom->texture[0];
	doom->settingui.minussound.rect = setirect(setivector2d(50, 110), 50, 50);
	//doom->settingui.minusmusic.texture = doom->texture[0];
	doom->settingui.plusmusic.rect = setirect(setivector2d(110, 50), 50, 50);
	//doom->settingui.plusmusic.texture = doom->texture[0];
	doom->settingui.minusmusic.rect = setirect(setivector2d(110, 110), 50, 50);
	//doom->settingui.minusmusic.texture = doom->texture[0];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optionmenu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 11:00:46 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/28 13:37:11 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawoptionmenu(t_doom *doom)
{
	drawrect(doom, doom->settingui.plussound.rect, setrgba(255, 255, 0, 0));
	drawrect(doom, doom->settingui.minussound.rect, setrgba(255, 255, 0, 0));

	drawrect(doom, doom->settingui.plusmusic.rect, setrgba(255, 255, 0, 0));
	drawrect(doom, doom->settingui.minusmusic.rect, setrgba(255, 255, 0, 0));
}

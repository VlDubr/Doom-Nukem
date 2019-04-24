/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitprogram.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:07:47 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/24 15:14:08 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			quitprogram(t_doom *doom)
{
	destrotwindow(doom);
	ft_memdel((void**)&doom);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}

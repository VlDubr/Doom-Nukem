/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmusic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:34:45 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/14 12:43:18 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Mix_Music	*loadmusic(char *path)
{
	Mix_Music *music;

	music = Mix_LoadMUS(path);
	if (music == NULL)
		error(ft_strjoin("Error: not loaded music ", path));
	ft_strdel(&path);
	return (music);
}

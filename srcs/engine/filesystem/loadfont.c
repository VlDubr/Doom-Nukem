/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfont.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:25:23 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:29:42 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		loadfont(char *path, t_doom *doom)
{
	char *p;

	p = ft_strjoin(path, "font.tga");
	doom->font = bitmap(p, setivector2d(28, 36));
	ft_strdel(&p);
	ft_strdel(&path);
}

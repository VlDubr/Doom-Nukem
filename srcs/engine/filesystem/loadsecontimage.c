/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsecontimage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:26:47 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:31:47 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_tga		*loadsecontimage(char *path)
{
	t_tga	*image;

	image = tga_reader(path);
	ft_strdel(&path);
	return (image);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:17:32 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 14:45:46 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	compress(void)
{
	int i;

	i = system("tar -cvf assets.tar assets");
	if (i)
		error("Error: not compress assets");
}

void	decompress(void)
{
	int i;

	i = system("tar -xvf assets.tar");
	if (i)
		error("Error: not decompress assets");
}

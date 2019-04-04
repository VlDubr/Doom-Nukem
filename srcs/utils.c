/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:50:55 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 13:51:17 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free2dstring(char **str)
{
	int	y;

	if (str)
	{
		y = 0;
		while (str[y] != NULL)
		{
			free(str[y]);
			str[y] = NULL;
			y++;
		}
		free(str);
		str = NULL;
	}
}

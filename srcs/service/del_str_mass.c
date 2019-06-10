/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_str_mass.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:13:45 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 16:01:35 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	del_str_mass(char **str)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_parse2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:52:24 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 18:22:34 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int	roof_vis(t_map *map, char *temp, int s_c)
{
	if (temp[0] == '-')
	{
		map->sector[s_c].r_visibility = 0;
		return (-ft_atoi(temp));
	}
	else
	{
		map->sector[s_c].r_visibility = 1;
		return (ft_atoi(temp));
	}
}

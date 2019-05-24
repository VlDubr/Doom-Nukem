/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/24 15:47:36 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static char	*s_m_w(t_map *map)
{
	int		i;
	char	*str;
	char	*del;

	i = 0;
	str = "";
	str = save_w(map, i, str);
	while (++i < map->wall_count)
	{
		del = str;
		str = save_w(map, i, str);
		free(del);
	}
	del = str;
	str = ft_strjoin(str, "\n");
	free(del);
	return (str);
}

static char	*s_m_s(t_map *map, char *str, int *i)
{
	char	*del;

	(*i) = 0;
	while ((*i) < map->sec_count)
	{
		del = str;
		str = save_s(map, (*i), str);
		free(del);
		(*i)++;
	}
	del = str;
	str = ft_strjoin(str, "\n");
	free(del);
	return (str);
}

void		save_map(t_map *map, t_serv *s)
{
	int		i;
	char	*str;
	char	*del;

	if (map->wall_count > 0)
	{
		str = s_m_w(map);
		str = s_m_s(map, str, &i);
		del = str;
		str = save_p(map, i, str);
		free(del);
		write(s->fd, str, sizeof(char) * ft_strlen(str));
	}
}

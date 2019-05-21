/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/21 18:32:09 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char *save_unit(int i, char *delim)
{
    char *str;
    char *del;

    str = ft_itoa(i);
    del = str;
    str = ft_strjoin(str, delim);
    free(del);
    return (str);
}

char *save_w(t_map *map, int i, char *str_old)
{
    char *del;
    char *str;

    str = ft_strjoin(str_old, "w: ");
    del = str;
    str = ft_strjoin(str, save_unit(map->walls[i].xy[0], ","));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->walls[i].xy[1], ","));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->walls[i].next_sec, ","));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->walls[i].next_type, "\n"));
    free(del);
    return (str);
}

char *save_s(t_map *map, int i, char *str_old)
{
    char *del;
    char *str;

    str = ft_strjoin(str_old, "s: ");
    del = str;
    str = ft_strjoin(str, save_unit(map->sector[i].start_pos, " "));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->sector[i].w_count, " "));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->sector[i].floor_h, " "));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->sector[i].roof_h, " "));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->sector[i].sec_type, "\n"));
    free(del);
    return (str);
}

char *save_p(t_map *map, int i, char *str_old)
{
    char *del;
    char *str;

    str = ft_strjoin(str_old, "p: ");
    del = str;
    str = ft_strjoin(str, save_unit(map->player.coords[0], ","));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->player.coords[1], " "));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->player.cam[0], ","));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->player.cam[1], ","));
    free(del);
    del = str;
    str = ft_strjoin(str, save_unit(map->player.cam[2], "\n"));
    free(del);
    return (str);
}

void save_map(t_map *map, t_serv *s)
{
	int i;
    char *str;
    char *del;

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

    i = 0;
    while (i < map->sec_count)
	{
        del = str;
        str = save_s(map, i, str);
        free(del);
		i++;
	}
    del = str;
    str = ft_strjoin(str, "\n");
    free(del);

    del = str;
    str = save_p(map, i, str);
    free(del);
    write(s->fd, str, sizeof(char) * ft_strlen(str));
}
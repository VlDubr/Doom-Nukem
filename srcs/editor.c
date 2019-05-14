/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:19:38 by srafe             #+#    #+#             */
/*   Updated: 2019/05/14 18:06:44 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/editor.h"

void	ft_error(const char *str)
{
	ft_putendl(str);
	exit(-1);
}

char	*file_read(int fd) 
{
	char	*buf;
	char	*str;
	int j;
	
	buf = (char *)malloc(sizeof(char) * 1000);
	str = malloc(0);

	if (fd == -1)
		ft_error("error");
	
	while ((j = read(fd, buf, 1000)) > 0)
	{
		buf[j] = '\0';
		str = ft_strjoin(str, buf);
	}
	return (str);
}

void malloc_data(t_map *map)
{
	int i;

	i = 0;
	map->sector = (t_sector	**)malloc(sizeof(t_sector *));
}

void	map_parser(char *str, t_map *map)
{
	int	i;
	int	w_c;
	int	s_c;

	w_c = 0;
	s_c = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'w')
			w_c++;
		if (str[i] == 's')
			s_c++;
		i++;
	}
	map->sec_count = s_c;
	map->wall_count = w_c;
	map->sector = (t_sector	*)malloc(sizeof(t_sector) * map->sec_count);
	map->walls = (t_wall *)malloc(sizeof(t_wall) * map->wall_count);
	
	i = 0;
	while (str[i] != '\0' && w_c > 0)
	{
		if (str[i] == 'w')
			// Написать парсер для карты. Тут должна считываться инфа для стен
		i++;
	}
}

void	editor(char *path) 
{
	int		fd;
	char	*str;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	fd = open(path, O_CREAT|O_RDWR, S_IWRITE|S_IREAD);
	str = file_read(fd);
	map_parser(str, map);
	//str = ft_strjoin(str, "ddddd\naaa");
	//write(fd, str, sizeof(char) * ft_strlen(str));
	close(fd);
}
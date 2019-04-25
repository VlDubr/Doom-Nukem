#include "doom.h"

void	loadwall(char **str, t_fvector **wall, size_t *count)
{
	char	**tmp;
	char	**tmp2;
	int		y;
	int		y2;

	y = 0;
	(*count) = 0;
	while (str[y] != NULL)
	{
		if (str[y][0] == 'w' && str[y][1] == ':')
			(*count)++;
		y++;
	}
	y = 0;
	y2 = 0;
	*wall = (t_fvector*)malloc(sizeof(t_fvector) * (*count));
	while (str[y] != NULL)
	{
		if (str[y][0] == 'w' && str[y][1] == ':')
		{
			tmp = ft_strsplit(str[y], ' ');
			tmp2 = ft_strsplit(tmp[1], ',');
			(*wall)[y2] = setfvector(ft_atoi(tmp2[0]), ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
			free2dstring(tmp);
			free2dstring(tmp2);
			y2++;
		}
		y++;
	}
}

void	loadsector(char **str, t_sector **sector, size_t *count)
{
	char	**tmp;
	int		y;
	int		y2;

	y = 0;
	(*count) = 0;
	while (str[y] != NULL)
	{
		if (str[y][0] == 's' && str[y][1] == ':')
			(*count)++;
		y++;
	}
	y = 0;
	y2 = 0;
	*sector = (t_sector*)malloc(sizeof(t_sector) * (*count));
	while (str[y] != NULL)
	{
		if (str[y][0] == 's' && str[y][1] == ':')
		{
			tmp = ft_strsplit(str[y], ' ');
			(*sector)[y2].start = ft_atoi(tmp[1]);
			(*sector)[y2].count = ft_atoi(tmp[2]);
			(*sector)[y2].floor = ft_atoi(tmp[3]);
			(*sector)[y2].height = ft_atoi(tmp[4]);
			(*sector)[y2].type = ft_atoi(tmp[5]);
			free2dstring(tmp);
			y2++;
		}
		y++;
	}
}

void	loadplayer(char	**str, t_player *player)
{
	int		y;
	int		flag;
	char	**tmp;
	char	**tmp2;

	y = 0;
	flag = 0;
	while (str[y] != NULL)
	{
		if (str[y][0] == 'p' && str[y][1] == ':')
		{
			if (!flag)
				flag = 1;
			else
				error("Error: player");
			tmp = ft_strsplit(str[y], ' ');
			tmp2 = ft_strsplit(tmp[1], ',');
			player->pos = setfvector(ft_atoi(tmp2[0]), 0, ft_atoi(tmp2[1]), 0);
			free2dstring(tmp2);
			tmp2 = ft_strsplit(tmp[2], ',');
			player->rotate = setfvector(ft_atoi(tmp2[0]), ft_atoi(tmp2[1]),
			ft_atoi(tmp2[2]), 0);
			free2dstring(tmp2);
			free2dstring(tmp);
		}
		y++;
	}
}

t_map	loadmap(char *path)
{
	t_map	r;
	char	*str;
	char	**tmp;

	str = readfile(path);
	tmp = ft_strsplit(str, '\n');
	loadwall(tmp, &r.walls, &r.wallcount);
	loadsector(tmp, &r.sectors, &r.sectorcount);
	loadplayer(tmp, &r.startplayer);
	free2dstring(tmp);
	ft_strdel(&str);
	return (r);
}

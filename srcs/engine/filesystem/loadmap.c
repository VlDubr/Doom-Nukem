#include "doom.h"

void	loadwall(char **str, t_fvector2d *wall, size_t *count)
{
	char	**tmp;
	char	**tmp2;
	int		y;
	int		y2;

	y = 0;
	*count = 0;
	while (str[y] != NULL)
	{
		if (str[y] == 'w' && str[y] == ':')
			*count++;
		y++;
	}
	y = 0;
	y2 = 0;
	wall = (t_fvector2d*)malloc(sizeof(t_fvector2d) * *count);
	while (y < *count)
	{
		if (str[y] == 'w' && str[y] == ':')
		{
			tmp = ft_strsplit(str[y], ' ');
			tmp2 = ft_strsplit(tmp, ',');
			wall[y2] = setfvector2d(ft_atoi(tmp2[0]), ft_atoi(tmp2[1]));
			free2dstring(tmp);
			free2dstring(tmp2);
			y2++;
		}
		y++;
	}
}

void	loadsector(char **str, t_sector *sector, size_t *count)
{
	char	**tmp;
	char	**tmp2;
	int		y;
	int		y2;
	int		y3;

	y = 0;
	*count = 0;
	while (str[y] != NULL)
	{
		if (str[y] == 's' && str[y] == ':')
			*count++;
		y++;
	}
	y = 0;
	y2 = 0;
	sector = (t_sector*)malloc(sizeof(t_sector) * *count);
	while (y < *count)
	{
		y3 = 0;
		if (str[y] == 's' && str[y] == ':')
		{
			tmp = ft_strsplit(str[y], ' ');
			sector[y2].floor = ft_atoi(tmp[1]);
			sector[y2].height = ft_atoi(tmp[2]);
			free2dstring(tmp);
			free2dstring(tmp2);
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
		}
		y++;
	}
}

t_map	loadmap(char *path)
{
	t_map	r;
	int		y;
	char	*str;
	char	**tmp;

	y = 0;
	str = readfile(path);
	tmp = ft_strsplit(tmp, '\n');
	while (tmp[y] != NULL)
	{
		loadwall(tmp, &r.walls, &r.wallcount);
		y++;
	}
	free2dstring(tmp);
	ft_strdel(str);
	return (r);
}

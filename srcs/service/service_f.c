/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 14:04:44 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	ft_error(const char *str)
{
	ft_putendl(str);
	exit(-1);
}

int		ft_max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

int		ft_str_chr_cpy(char *temp, char *str, int i, char *chr)
{
	int		j;

	j = 0;
	while (str[i] != chr[0] && str[i] != chr[1] && str[i] != chr[2])
	{
		temp[j] = str[i];
		i++;
		j++;
	}
	if (str[i] == chr[2] && chr[3] != 49)
		ft_error("Map not valid");
	temp[j] = '\0';
	return (i + 1);
}

int		check_w_entry(t_sector *s, int count, int comp)
{
	if ((s[count].start_pos <= comp &&
		comp < (s[count].start_pos + s[count].w_count)))
		return (1);
	return (0);
}

char	*file_read(int fd, char *file)
{
	char	buf[1001];
	char	*str;
	char	*del;
	int		j;

	fd = open(file, O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
	str = malloc(0);
	if (fd == -1)
		ft_error("Read file error!");
	while ((j = read(fd, buf, 1000)) > 0)
	{
		del = str;
		buf[j] = '\0';
		str = ft_strjoin(str, buf);
		ft_strdel(&del);
	}
	return (str);
}

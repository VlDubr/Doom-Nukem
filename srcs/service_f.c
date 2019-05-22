/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/22 13:09:59 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

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
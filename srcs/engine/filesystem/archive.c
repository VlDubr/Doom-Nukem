/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:17:32 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 19:30:04 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	compress(char *path)
{
	char	*command;
	int		i;

	command = ft_strjoin("tar -cvf ", path);
	i = system(command);
	ft_strdel(&path);
	ft_strdel(&command);
	if (i)
		error("Error: not compress assets");
}

void	decompress(char *path)
{
	char	*command;
	int		i;

	command = ft_strjoin("tar -xvf ", path);
	i = system(command);
	ft_strdel(&path);
	ft_strdel(&command);
	if (i)
		error("Error: not decompress assets");
}

void	unixcommand(char *command)
{
	int		i;

	i = system(command);
	ft_strdel(&command);
	if (i)
		error("Error: not decompress assets");
}

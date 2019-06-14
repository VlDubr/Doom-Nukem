/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:44:30 by srafe             #+#    #+#             */
/*   Updated: 2019/06/14 17:40:11 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	compress(char *path)
{
	char	*command;
	int		i;

	command = ft_strjoin("tar -cvf ", path);
	i = system(command);
	ft_strdel(&path);
	ft_strdel(&command);
	if (i)
		ft_error("Error: not compress assets");
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
		ft_error("Error: not decompress assets");
}

void	unixcommand(char *command)
{
	int		i;

	i = system(command);
	ft_strdel(&command);
	if (i)
		ft_error("Error: not decompress assets");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileexist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:50:31 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 15:53:48 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filesystem.h"

int		fileexist(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd > -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

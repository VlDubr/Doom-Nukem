/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializeint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:05:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 17:32:33 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		serializeint(int fd, char *name, int nb)
{
	char *tmp[3];

	tmp[0] = ft_itoa(nb);
	tmp[1] = ft_strjoin(name, ": ");
	tmp[2] = ft_strjoin(tmp[1], tmp[0]);
	ft_putendl_fd(tmp[2], fd);
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	ft_strdel(&tmp[2]);
}

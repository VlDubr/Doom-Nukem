/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/18 18:16:00 by srafe            ###   ########.fr       */
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
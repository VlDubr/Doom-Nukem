/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:47:22 by srafe             #+#    #+#             */
/*   Updated: 2019/04/15 15:29:36 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tga.h"

void	ft_error(const char *str)
{
	ft_putendl(str);
	exit(-1);
}

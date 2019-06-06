/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:09:21 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/03 19:09:22 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filesystem.h"

char		*getpath(const char *argv0)
{
	char	*r;
	size_t	len;

	len = ft_strlen(argv0);
	while (argv0[len] != '/')
		len--;
	len++;
	r = ft_strsub(argv0, 0, len);
	return (r);
}

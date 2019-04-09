/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserializeint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:09:11 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 12:38:01 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		deserializeint(char *str, char *name)
{
	int		r;
	char	**tmp;

	if (ft_strnequ(name, str, ft_strlen(name)))
	{
		tmp = ft_strsplit(str, ' ');
		r = ft_atoi(tmp[1]);
		free2dstring(tmp);
		return (r);
	}
	return (0);
}

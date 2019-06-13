/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 12:18:04 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 17:14:46 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	result;
	double	power;
	int		sign;

	while ((*str) && ft_isspace(*str))
		str++;
	sign = 1;
	if (*str && *str == '-')
	{
		sign = -1;
		str++;
	}
	result = 0;
	while ((*str) && ft_isdigit(*str))
		result = 10 * result + *str++ - '0';
	if (*str && *str == '.')
		str++;
	power = 1;
	while ((*str) && ft_isdigit(*str))
	{
		result = 10 * result + *str++ - '0';
		power *= 10;
	}
	return (sign * result / power);
}

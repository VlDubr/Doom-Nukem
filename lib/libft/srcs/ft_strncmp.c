/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:50:16 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:21:43 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *string1, const char *string2, size_t len)
{
	unsigned char *str1;
	unsigned char *str2;

	str1 = (unsigned char *)string1;
	str2 = (unsigned char *)string2;
	while (len--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		if (*str1 == '\0' && *str2 == '\0')
			return (0);
		str1++;
		str2++;
	}
	return (0);
}

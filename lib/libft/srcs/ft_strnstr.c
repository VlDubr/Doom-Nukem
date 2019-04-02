/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:43:44 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:21:53 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	int		length;
	int		lens2;

	length = len;
	lens2 = ft_strlen(str2);
	while (*str1 && len--)
	{
		if (length-- < lens2)
			return (NULL);
		if (ft_memcmp(str1, str2, lens2) == 0)
			return ((char *)str1);
		str1++;
	}
	return (NULL);
}

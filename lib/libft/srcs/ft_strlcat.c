/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:29:01 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:21:27 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *str, size_t len)
{
	size_t		lendest;
	size_t		lenstr;

	lendest = ft_strlen(dest);
	lenstr = ft_strlen(str);
	if (len < lendest)
		return (lenstr + len);
	while (len-- - 1 > lendest && *str)
		*(dest++ + lendest) = *(str++);
	*(dest + lendest) = '\0';
	return (lendest + lenstr);
}

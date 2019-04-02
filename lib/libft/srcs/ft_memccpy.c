/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:21:35 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:20:01 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *str, int c, size_t len)
{
	unsigned char			*buff;
	const unsigned char		*src;
	unsigned char			sym;
	int						i;

	buff = (unsigned char *)dest;
	src = (const unsigned char *)str;
	sym = (unsigned char)c;
	i = 0;
	while (len--)
	{
		i++;
		if (*src == sym)
		{
			*buff++ = *src++;
			return (dest += i);
		}
		else
			*buff++ = *src++;
	}
	return (NULL);
}

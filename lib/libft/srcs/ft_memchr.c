/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:31:50 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:20:03 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t len)
{
	const unsigned char		*src;
	unsigned char			sym;

	src = (const unsigned char *)str;
	sym = (unsigned char)c;
	while (len--)
	{
		if (*src == sym)
			return ((void *)src);
		src++;
	}
	return (NULL);
}

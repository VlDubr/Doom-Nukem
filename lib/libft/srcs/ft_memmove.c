/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:51:50 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:20:15 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *str, size_t len)
{
	unsigned char			*buff;
	unsigned const char		*src;

	if (dest == str)
		return (dest);
	if (!dest || !str)
		return (NULL);
	buff = (unsigned char *)dest;
	src = (unsigned const char *)str;
	if (src > buff)
		while (len--)
			*buff++ = *src++;
	else
		while (len--)
			*(buff + len) = *(src + len);
	return (dest);
}

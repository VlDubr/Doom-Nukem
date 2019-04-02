/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:03:56 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:21:46 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *str, size_t len)
{
	char	*buff;

	buff = dest;
	while (len--)
		if (*str == '\0')
			*buff++ = '\0';
		else
			*buff++ = *str++;
	return (dest);
}

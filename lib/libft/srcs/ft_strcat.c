/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:09:20 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:20:51 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *str)
{
	char		*buff;
	size_t		len;

	buff = dest;
	len = ft_strlen(buff);
	buff = &buff[len];
	while (*str)
		*buff++ = *str++;
	*buff = '\0';
	return (dest);
}

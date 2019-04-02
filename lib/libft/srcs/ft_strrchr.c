/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:17:17 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:21:56 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		len;

	len = ft_strlen(str);
	if ((const char)c == '\0')
		return (ft_strchr(str, '\0'));
	while (len--)
		if (*(str + len) == (const char)c)
			return ((char *)str + len);
	return (NULL);
}

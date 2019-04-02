/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:59:44 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:21:09 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*buff;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if (!(buff = (char *)(malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	while (len-- >= 0)
	{
		buff[i] = str[i];
		i++;
	}
	return (buff);
}

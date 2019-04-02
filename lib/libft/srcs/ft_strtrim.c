/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:41:15 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:45:27 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*str;
	size_t		len;
	size_t		i;
	size_t		k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = ft_whitespaces(&s, len);
	if (!(str = malloc(sizeof(char) * (len - i + 1))))
		return (NULL);
	while (k < len - i)
		str[k++] = *s++;
	str[k] = '\0';
	return (str);
}

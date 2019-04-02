/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitespaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:57:17 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:45:36 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_whitespaces(char const **s, size_t len)
{
	size_t	i;

	i = 0;
	while (**s)
	{
		if (**s == ' ' || **s == '\t' || **s == '\n')
		{
			(*s)++;
			i++;
		}
		else if (*(*s + len - i - 1) == ' ' ||
			*(*s + len - i - 1) == '\t' || *(*s + len - i - 1) == '\n')
			i++;
		else
			break ;
	}
	return (i);
}

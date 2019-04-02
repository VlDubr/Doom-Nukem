/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:06:35 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:18:38 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*num;
	int		i;
	int		len;
	int		flag;

	if (n == -2147483648)
		return (ft_strsub("-2147483648", 0, 12));
	i = 0;
	flag = 0;
	len = ft_count(n);
	if (n < 0)
	{
		if (!(num = ft_strnew(len + 1)))
			return (NULL);
		*num++ = '-';
		flag = 1;
		n = -n;
	}
	else if (n >= 0)
		if (!(num = ft_strnew(len)))
			return (NULL);
	while (++i <= len)
		*num++ = (n / ft_power(10, len - i)) % 10 + 48;
	return (num - len - flag);
}

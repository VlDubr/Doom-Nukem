/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:37:17 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 17:05:59 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ftoa(double num, int count)
{
	char	*str;
	char	*del;
	char	*del2;
	int		temp;

	temp = (int)num;
	str = ft_itoa(temp);
	num -= (double)temp;
	if ((num != 0.0 && num > 0.00001) || num < -0.00001)
	{
		del = str;
		str = ft_strjoin(str, ".");
		ft_strdel(&del);
		while (num != 0.0 && count > 0)
		{
			num *= 10;
			temp = (int)num;
			num -= (double)temp;
			del = str;
			del2 = ft_itoa(temp);
			str = ft_strjoin(str, del2);
			ft_strdel(&del);
			ft_strdel(&del2);
			count--;
		}
	}
	return (str);
}

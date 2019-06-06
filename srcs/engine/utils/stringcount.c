/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:50:18 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/03 18:50:31 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

size_t		stringcount(char **str)
{
	size_t count;

	count = 0;
	while (str[count] != NULL)
		count++;
	return (count);
}
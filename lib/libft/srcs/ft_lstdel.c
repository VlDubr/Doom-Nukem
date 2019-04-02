/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:17:43 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:18:53 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list		*buff;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		buff = (*alst)->next;
		(del)((*alst)->content, (*alst)->content_size);
		free(*alst);
		(*alst) = buff;
	}
	*alst = NULL;
}

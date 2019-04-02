/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:00:02 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:19:16 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*newlist;
	void		*contentcpy;

	if (!(newlist = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		newlist->content = NULL;
		newlist->content_size = 0;
		newlist->next = NULL;
		return (newlist);
	}
	if (!(contentcpy = malloc(content_size)))
	{
		free(newlist);
		return (NULL);
	}
	ft_memcpy(contentcpy, content, content_size);
	newlist->content = contentcpy;
	newlist->content_size = content_size;
	newlist->next = NULL;
	return (newlist);
}

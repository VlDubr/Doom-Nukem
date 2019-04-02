/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 17:15:30 by wqarro-v          #+#    #+#             */
/*   Updated: 2019/03/18 12:45:40 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelete_element(t_list **alst, int fd)
{
	t_list		*tmppre;
	t_list		*tmp;

	tmppre = *alst;
	tmp = *alst;
	while (tmp->content_size != (size_t)fd)
	{
		tmppre = tmp;
		tmp = tmp->next;
	}
	if (tmp == *alst)
		*alst = tmp->next;
	tmppre->next = tmp->next;
	if (tmp->content != NULL)
		free(tmp->content);
	free(tmp);
}

t_list		*find_tmp_fd(t_list *list, int fd)
{
	t_list		*tmp;

	tmp = list;
	while (tmp && tmp->next != NULL && tmp->content_size != (size_t)fd)
		tmp = tmp->next;
	return (tmp);
}

int			create_line(t_list **tmp, char **line)
{
	int		i;
	char	*str;

	i = 0;
	while (((char *)((*tmp)->content))[i] != '\n' &&
		((char *)((*tmp)->content))[i] != '\0')
		i++;
	*line = ft_strsub((*tmp)->content, 0, i);
	str = (*tmp)->content;
	(*tmp)->content = ft_strsub((*tmp)->content, i + 1,
		ft_strlen((*tmp)->content) - i);
	ft_strdel(&str);
	return (1);
}

t_list		*get_list(int fd, t_list **list, char *buf)
{
	t_list		*tmp;
	char		*str;

	if (!*list)
	{
		*list = ft_lstnew(buf, ft_strlen(buf) + 1);
		(*list)->content_size = fd;
		tmp = *list;
		return (tmp);
	}
	tmp = find_tmp_fd(*list, fd);
	if (tmp->content_size == (size_t)fd)
	{
		str = tmp->content;
		tmp->content = ft_strjoin(tmp->content, buf);
		ft_strdel(&str);
	}
	else
	{
		tmp->next = ft_lstnew(buf, ft_strlen(buf) + 1);
		tmp = tmp->next;
		tmp->content_size = fd;
	}
	return (tmp);
}

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static t_list	*list = NULL;
	t_list			*tmp;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	tmp = find_tmp_fd(list, fd);
	if (tmp && tmp->content_size == (size_t)fd && ft_strchr(tmp->content, '\n'))
		return (create_line(&tmp, line));
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = get_list(fd, &list, buf);
		if (ft_strchr(tmp->content, '\n'))
			break ;
	}
	if (tmp && tmp->content_size == (size_t)fd && *((char *)(tmp)->content))
		return (create_line(&tmp, line));
	else
	{
		if (tmp && tmp->content_size == (size_t)fd)
			ft_lstdelete_element(&list, fd);
		return (0);
	}
}

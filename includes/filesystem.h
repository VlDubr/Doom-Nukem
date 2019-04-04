/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:52:02 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 17:25:11 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEM_H
# define FILESYSTEM_H
# include "../lib/libft/includes/libft.h"
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFF_SIZE
#  define BUFF_SIZE 100
# endif
# ifdef __APPLE__
#  define CREATEFLAG S_IWOTH | S_IREAD
# elif __linux__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
# endif

int		fileexist(char *path);
char	*readfile(char *path);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:52:02 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 14:35:21 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEM_H
# define FILESYSTEM_H
# include "../lib/libft/includes/libft.h"
# include "doom.h"
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFF_SIZE
#  define BUFF_SIZE 100
# endif
# define SINT(fd, name) (serializeint(fd, #name, name))
# define DSINT(str, int) (deserializeint(str, #int))

int			fileexist(char *path);
char		*readfile(char *path);
char		*getpath(const char *argv0);

void		compress(void);
void		decompress(void);

int			deserializeint(char *str, char *name);
void		serializeint(int fd, char *name, int nb);

#endif

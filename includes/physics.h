/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:03:07 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 18:57:28 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H
# include "doom.h"
# define SIGN(value) (value / abs(value))

typedef struct	s_line
{
	t_fvector2d a1;
	t_fvector2d a2;
	t_fvector2d b1;
	t_fvector2d b2;
}				t_line;
t_line			setline(t_fvector2d a1, t_fvector2d a2,
t_fvector2d b1, t_fvector2d b2);

int				collideline(t_line line);

#endif

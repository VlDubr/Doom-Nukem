/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousemove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:32:56 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/31 15:26:41 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	camerarotate(t_player *play, t_input *input)
{
	play->rotate.z -= input->deltapos.x;
	play->rotate.x += input->deltapos.y;
}

void	mousemove(t_player *play, t_input *input, float delta)
{
	input->deltapos.x = ((input->old.x - input->mousepos.x) * input->sensivety);
	input->deltapos.y = ((input->old.y - input->mousepos.y) * input->sensivety);
	input->old = input->mousepos;
	camerarotate(play, input);
}

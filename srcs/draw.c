/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:02:57 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawwalls(t_doom *doom)
{
	t_list	*tmp;
	t_wall	*wall;

	tmp = doom->pipeline;
	while (tmp != NULL)
	{
		wall = (t_wall*)tmp->content;
		if (wall->type != 2)
			drawwall(doom->win->pixels, *wall, wall->texture, wall->offset);
		tmp = tmp->next;
	}
}

void	proj(t_doom *doom, t_mat4x4 projec, t_wall wa)
{
	if (clip(wa.p, wa.offset))
	{
		wallproj(wa.p, projec);
		if (wa.p[0].x > wa.p[1].x)
		{
			ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
			ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);
			ft_swap((void**)&wa.offset[1], (void**)&wa.offset[0]);
		}
		addwallinlist(&doom->pipeline, wa);
	}
}

void	loopdrawwall(t_doom *doom, t_list *wa, t_sermat mat)
{
	t_wall *wall;
	t_list *tmp;

	tmp = wa;
	while (tmp != NULL)
	{
		wall = (t_wall*)tmp->content;
		multmatrixdrawwall(wall->p, mat.cammat);
		proj(doom, mat.projec, *wall);
		tmp = tmp->next;
	}
}

void	drawwallv3(t_doom *doom, size_t sec)
{
	t_list		*wa;
	t_sermat	mat;
	t_sector	sect;
	t_ivector	ci;

	mat.cammat = matcam(&doom->player);
	mat.projec = matprojection(initcam(setivector2d(800, 800)));
	sect = doom->thismap.sectors[sec];
	ci.x = sect.start;
	ci.y = -1;
	doom->visit[sec] = 1;
	while ((size_t)++ci.y < sect.count)
	{
		wa = NULL;
		setwalls(doom, &wa, sect, ci);
		loopdrawwall(doom, wa, mat);
		ft_lstdel(&wa, del);
	}
}

void	draw(t_doom *doom)
{
	doom->pipeline = NULL;
	drawwallv3(doom, doom->player.sector);
	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);
	drawskubox(doom);
	drawobj(doom, doom->thismap);
	drawsort(doom->pipeline);
	drawwalls(doom);
	ft_lstdel(&doom->pipeline, del);
	drawminimap(doom->win->pixels, doom, doom->player.sector,
	setivector2d(400, 300));
	drawweapon(doom);
	drawammo(doom);
	drawui(doom);
	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}

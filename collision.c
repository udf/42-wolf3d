/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 22:22:40 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/09 23:25:14 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	is_in_solid_cell(t_env *e, t_p2d pos)
{
	const t_ip2d	cpos = {(ssize_t)pos.x, (ssize_t)pos.y};
	t_cell			*cell;

	if (cpos.x < 0 || cpos.x >= e->world_w)
		return (1);
	if (cpos.y < 0 || cpos.y >= e->world_h)
		return (1);
	cell = vec_get_2d(&e->world,
		(size_t)cpos.x, (size_t)cpos.y, (size_t)e->world_w);
	if (cell->type == WALL)
		return 1;
	if (cell->type == DOOR && cell->door.anim_state == 0)
		return 1;
	return (0);
}

void	process_collision(t_env *e, t_p2d offset)
{
	const t_p2d		new_pos = {e->me.pos.x + offset.x, e->me.pos.y + offset.y};
	const t_p2d		old_pos = e->me.pos;

	e->me.pos = new_pos;
	if (is_in_solid_cell(e, old_pos) || !is_in_solid_cell(e, new_pos))
		return ;
	e->me.pos.x = new_pos.x;
	e->me.pos.y = old_pos.y;
	if (!is_in_solid_cell(e, e->me.pos))
		return ;
	e->me.pos.x = old_pos.x;
	e->me.pos.y = new_pos.y;
	if (!is_in_solid_cell(e, e->me.pos))
		return ;
	e->me.pos = old_pos;
}

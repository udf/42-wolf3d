/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 22:22:40 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/10 11:13:01 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	is_in_solid_cell(t_env *e, t_p2d pos)
{
	const t_ip2d	cpos = {(ssize_t)pos.x, (ssize_t)pos.y};
	t_cell			*cell;

	cell = get_cell(e, cpos);
	if (!cell)
		return (1);
	if (cell->type == WALL)
		return (1);
	if (cell->type == DOOR && cell->door.anim_state == 0)
		return (1);
	return (0);
}

static int	try_operate_door(t_env *e, t_p2d pos)
{
	const t_ip2d	cpos = {(ssize_t)pos.x, (ssize_t)pos.y};
	t_cell			*cell;
	t_cell_key		**slot;

	if (!(cell = get_cell(e, cpos)) || cell->type != DOOR)
		return 0;
	if (cell->door.anim_state > 0)
		return 0;
	slot = NULL;
	if (e->me.key2 && e->me.key2->colour == cell->door.colour)
		slot = &e->me.key2;
	if (e->me.key1 && e->me.key1->colour == cell->door.colour)
		slot = &e->me.key1;
	if (!slot)
		return (0);
	(*slot)->respawn_ticks = 6000;
	*slot = NULL;
	cell->door.open_ticks = 6000;
	printf("opening door at %zd %zd\n", cpos.x, cpos.y);
	return 1;
}

void		process_collision(t_env *e, t_p2d offset)
{
	const t_p2d		new_pos = {e->me.pos.x + offset.x, e->me.pos.y + offset.y};
	const t_p2d		old_pos = e->me.pos;

	e->me.pos = new_pos;
	if (is_in_solid_cell(e, old_pos) || !is_in_solid_cell(e, new_pos))
		return ;
	if (try_operate_door(e, new_pos))
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

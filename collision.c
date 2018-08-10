/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 22:22:40 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/10 14:07:01 by mhoosen          ###   ########.fr       */
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

void		process_collision(t_env *e, t_p2d *target, t_p2d offset)
{
	const t_p2d		new_pos = {target->x + offset.x, target->y + offset.y};
	const t_p2d		old_pos = *target;

	*target = new_pos;
	if (is_in_solid_cell(e, old_pos) || !is_in_solid_cell(e, new_pos))
		return ;
	if (try_operate_door(e, new_pos))
		return ;
	target->x = new_pos.x;
	target->y = old_pos.y;
	if (!is_in_solid_cell(e, *target))
		return ;
	target->x = old_pos.x;
	target->y = new_pos.y;
	if (!is_in_solid_cell(e, *target))
		return ;
	*target = old_pos;
}

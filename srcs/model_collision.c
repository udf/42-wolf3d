/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 22:51:51 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 21:18:57 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static int	is_in_solid_cell(t_p2d pos)
{
	const t_cell *cell = model_get_cell(pos);

	if (!cell)
		return (1);
	if (cell->type == WALL)
		return (1);
	if (cell->type == DOOR && cell->door->anim_state == 0)
		return (1);
	return (0);
}

static int	try_operate_door(t_p2d pos)
{
	const t_cell	*cell = model_get_cell(pos);
	t_model_data	*m;
	t_key			**slot;

	m = model_get_real();
	if (!cell || cell->type != DOOR)
		return (0);
	if (cell->door->anim_state > 0)
		return (0);
	slot = NULL;
	if (m->me.key2 && m->me.key2->colour == cell->door->colour)
		slot = &m->me.key2;
	if (m->me.key1 && m->me.key1->colour == cell->door->colour)
		slot = &m->me.key1;
	if (!slot)
		return (0);
	(*slot)->respawn_ticks = 6000;
	*slot = NULL;
	((t_cell *)cell)->door->open_ticks = 6000;
	printf("opening door at %zd %zd\n", (ssize_t)pos.x, (ssize_t)pos.y);
	return (1);
}

int			model_do_collision(t_p2d *target, t_p2d offset)
{
	const t_p2d		new_pos = {target->x + offset.x, target->y + offset.y};
	const t_p2d		old_pos = *target;

	*target = new_pos;
	if (is_in_solid_cell(old_pos) || !is_in_solid_cell(new_pos))
		return (0);
	if (try_operate_door(new_pos))
		return (0);
	target->x = new_pos.x;
	target->y = old_pos.y;
	if (!is_in_solid_cell(*target))
		return (1);
	target->x = old_pos.x;
	target->y = new_pos.y;
	if (!is_in_solid_cell(*target))
		return (1);
	*target = old_pos;
	return (1);
}

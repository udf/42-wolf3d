/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 09:42:00 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/10 13:48:38 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	do_animations(t_cell *cell, t_cell *p_cell,
	ssize_t ticks, float secs)
{
	float tmp;

	if (cell->type == DOOR)
	{
		cell->door.open_ticks = (short)MAX(cell->door.open_ticks - ticks, 0);
		if (cell == p_cell && cell->door.open_ticks <= 0)
			return ;
		tmp = (float)cell->door.anim_state;
		tmp += (secs * 100) * (cell->door.open_ticks > 0 ? 1.0f : -1.0f);
		cell->door.anim_state = (char)CLAMP(tmp, 0.0f, 100.0f);
	}
	if (cell->type == KEY && cell->key.respawn_ticks > 0)
	{
		cell->key.respawn_ticks = (short)MAX(cell->key.respawn_ticks - ticks, 0);
		if (cell->key.respawn_ticks <= 0)
		{
			printf("key respawn\n");
			cell->key.held = 0;
		}
	}
}

static void	try_pick_up(t_player *me, t_cell *cell)
{
	t_cell_key	**slot;

	if (cell->type != KEY || cell->key.held)
		return ;
	slot = NULL;
	if (me->key2 == NULL)
		slot = &me->key2;
	if (me->key1 == NULL)
		slot = &me->key1;
	if (!slot || p2d_dist(me->pos, cell->key.pos) > 0.5f)
		return ;
	if (cell->key.colour == 0)
	{
		me->exit = 1;
		return ;
	}
	*slot = &cell->key;
	(*slot)->held = 1;
}

void		process_logic(t_env *e, ssize_t ticks)
{
	const float	secs = (float)ticks / 1000.0f;
	size_t		i;
	t_cell		*p_cell;
	t_cell		*cell;

	i = 0;
	p_cell = get_cell(e, (t_ip2d){(ssize_t)e->me.pos.x, (ssize_t)e->me.pos.y});
	while (i < e->world.length)
	{
		cell = vec_get(&e->world, i);
		try_pick_up(&e->me, cell);
		do_animations(cell, p_cell, ticks, secs);
		i++;
	}
}

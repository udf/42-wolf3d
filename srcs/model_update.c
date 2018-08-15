/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 23:06:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/15 00:19:49 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void	update_doors(t_model_data *m, ssize_t ticks, float secs)
{
	const t_cell	*p_c = model_get_cell(m->me.pos);
	const t_door	*p_door = (p_c && p_c->type == DOOR) ? p_c->door : NULL;
	size_t		i;
	t_door		*door;
	float		tmp;

	i = 0;
	while (i < m->world.doors.length)
	{
		door = vec_get(&m->world.doors, i);
		i++;
		door->open_ticks = (short)MAX(door->open_ticks - ticks, 0);
		if (door == p_door && door->open_ticks <= 0)
			continue ;
		tmp = (float)door->anim_state;
		tmp += (secs * 100) * (door->open_ticks > 0 ? 1.0f : -1.0f);
		door->anim_state = (char)CLAMP(tmp, 0.0f, 100.0f);
	}
}

static void	try_pick_up(t_player *me, t_key *key)
{
	t_key	**slot;

	if (key->held)
		return ;
	slot = NULL;
	if (me->key2 == NULL)
		slot = &me->key2;
	if (me->key1 == NULL)
		slot = &me->key1;
	if (!slot || p2d_dist(me->pos, key->pos) > 0.5f)
		return ;
	if (key->colour == 0)
	{
		post_exit_event();
		return ;
	}
	*slot = key;
	(*slot)->held = 1;
}

static void	update_keys(t_model_data *m, ssize_t ticks)
{
	size_t		i;
	t_thing		*thing;
	t_key		*key;

	i = 0;
	while (i < m->world.things.length)
	{
		thing = vec_get(&m->world.things, i);
		i++;
		if (thing->type != KEY)
			continue ;
		key = &thing->key;
		try_pick_up(&m->me, key);
		if (key->respawn_ticks <= 0)
			continue ;
		key->respawn_ticks = (short)MAX(key->respawn_ticks - ticks, 0);
		if (key->respawn_ticks <= 0)
		{
			printf("key respawn\n");
			key->held = 0;
		}
	}
}

void		model_update(ssize_t elapsed_ticks, float elapsed_secs)
{
	t_model_data	*m;
	m = model_get_real();
	update_doors(m, elapsed_ticks, elapsed_secs);
	update_keys(m, elapsed_ticks);
}

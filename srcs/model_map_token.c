/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_map_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 18:49:53 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/18 14:25:20 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	process_player_token(t_player *me, char c, t_ip2d pos)
{
	float	rot;

	rot = NAN;
	if (c == 'e')
		rot = 0.0f;
	if (c == 's')
		rot = 90.0f;
	if (c == 'w')
		rot = 180.0f;
	if (c == 'n')
		rot = 270.0f;
	if (isnan(rot))
		return (1);
	me->rot = rot;
	me->pos = (t_p2d){(float)pos.x + 0.5f, (float)pos.y + 0.5f};
	return (0);
}

int	process_wall_token(t_cell *cell, t_wall walls[256], char c)
{
	static char			tmp_name[4] = {'W', '\0', '\0', '\0'};
	const unsigned char	i = (unsigned char)c;

	if (!walls[i].tex_n)
	{
		tmp_name[1] = c;
		tmp_name[2] = 'n';
		if (!(walls[i].tex_n = texture_sys_get(tmp_name)))
			return (1);
		tmp_name[2] = 's';
		if (!(walls[i].tex_s = texture_sys_get(tmp_name)))
			return (1);
		tmp_name[2] = 'w';
		if (!(walls[i].tex_w = texture_sys_get(tmp_name)))
			return (1);
		tmp_name[2] = 'e';
		if (!(walls[i].tex_e = texture_sys_get(tmp_name)))
			return (1);
	}
	cell->type = WALL;
	cell->wall = &walls[i];
	return (0);
}

int	process_door_token(t_cell *cell, t_vec *doors, char c)
{
	static char	tmp_name[3] = {'D', '\0', '\0'};
	t_door		door;

	tmp_name[1] = c;
	if (!(door.tex = texture_sys_get(tmp_name)))
		return (1);
	door.open_ticks = 0;
	door.anim_state = 0;
	door.colour = c;
	vec_append(doors, &door);
	cell->type = DOOR;
	cell->door = (t_door *)(doors->length - 1);
	return (0);
}

int	process_key_token(t_vec *things, char c, t_ip2d pos)
{
	static char	tmp_name[3] = {'K', '\0', '\0'};
	t_thing		thing;

	tmp_name[1] = c;
	if (!(thing.key.tex = texture_sys_get(tmp_name)))
		return (1);
	thing.type = KEY;
	thing.key.respawn_ticks = 0;
	thing.key.held = 0;
	thing.key.colour = c;
	thing.key.pos.x = (float)pos.x + 0.5f;
	thing.key.pos.y = (float)pos.y + 0.5f;
	thing.key.o_pos = thing.key.pos;
	thing.key.rot_off = (float)rand() / (float)RAND_MAX * 360.0f;
	vec_append(things, &thing);
	return (0);
}

int	process_prop_token(t_vec *things, char c, t_ip2d pos)
{
	static char	tmp_name[3] = {'P', '\0', '\0'};
	t_thing		thing;

	tmp_name[1] = c;
	if (!(thing.prop.tex = texture_sys_get(tmp_name)))
		return (1);
	thing.type = PROP;
	thing.prop.pos.x = (float)pos.x + 0.5f;
	thing.prop.pos.y = (float)pos.y + 0.5f;
	vec_append(things, &thing);
	return (0);
}

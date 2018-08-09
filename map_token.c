/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 18:49:53 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/09 19:37:04 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	process_player_token(t_cell *cell, char c, t_env *e, t_ip2d pos)
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
		return ;
	e->me.rot = rot;
	e->me.pos = (t_p2d){(float)pos.x + 0.5f, (float)pos.y + 0.5f};
	cell->type = EMPTY;
}

void	process_wall_token(t_cell *cell, char c)
{
	static char		tmp_name[4] = {'W', '\0', '\0', '\0'};

	tmp_name[1] = c;
	tmp_name[2] = 'n';
	if (!(cell->wall.tex_n = texture_sys_get(tmp_name)))
		return ;
	tmp_name[2] = 's';
	if (!(cell->wall.tex_s = texture_sys_get(tmp_name)))
		return ;
	tmp_name[2] = 'w';
	if (!(cell->wall.tex_w = texture_sys_get(tmp_name)))
		return ;
	tmp_name[2] = 'e';
	if (!(cell->wall.tex_e = texture_sys_get(tmp_name)))
		return ;
	cell->type = WALL;
}

void	process_door_token(t_cell *cell, char c)
{
	static char		tmp_name[3] = {'D', '\0', '\0'};

	tmp_name[1] = c;
	if (!(cell->door.tex = texture_sys_get(tmp_name)))
		return ;
	cell->door.open_ticks = 0;
	cell->door.anim_state = 0;
	cell->door.colour = c;
	cell->type = DOOR;
}

void	process_key_token(t_cell *cell, char c)
{
	static char		tmp_name[3] = {'K', '\0', '\0'};

	tmp_name[1] = c;
	if (!(cell->key.tex = texture_sys_get(tmp_name)))
		return ;
	cell->key.respawn_ticks = 0;
	cell->key.held = 0;
	cell->key.colour = c;
	cell->type = DOOR;
}

void	process_prop_token(t_cell *cell, char c)
{
	static char		tmp_name[3] = {'P', '\0', '\0'};

	tmp_name[1] = c;
	if (!(cell->prop.tex = texture_sys_get(tmp_name)))
		return ;
	cell->type = PROP;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 21:36:33 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/15 00:24:08 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

void	model_player_move(float amount)
{
	t_model_data	*m;
	t_p2d			offset;

	m = model_get_real();
	offset.x = cos_deg(m->me.rot) * amount;
	offset.y = sin_deg(m->me.rot) * amount;
	model_do_collision(&m->me.pos, offset);
}

void	model_player_rotate(float amount)
{
	t_model_data	*m;

	m = model_get_real();
	m->me.rot = mod_deg(m->me.rot + amount);
}

void	model_player_drop_key(int num)
{
	t_key	**slot;
	t_model_data	*m;

	m = model_get_real();
	slot = NULL;
	slot = (num == 1) ? &m->me.key1 : slot;
	slot = (num == 2) ? &m->me.key2 : slot;
	if (!slot || !*slot)
		return ;
	(*slot)->held = 0;
	(*slot)->pos = m->me.pos;
	(*slot)->respawn_ticks = 0;
	model_do_collision(&(*slot)->pos,
		(t_p2d){cos_deg(m->me.rot) * 0.75f, sin_deg(m->me.rot) * 0.75f});
	*slot = NULL;
}

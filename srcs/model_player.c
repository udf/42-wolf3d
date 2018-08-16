/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 21:36:33 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 22:17:33 by mhoosen          ###   ########.fr       */
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
	model_do_collision(&m->me.pos, offset, 1);
}

void	model_player_rotate(float amount)
{
	t_model_data	*m;

	m = model_get_real();
	m->me.rot = mod_deg(m->me.rot + amount);
}

void	model_player_drop_key(int num)
{
	t_key			*key;
	t_key			**slot;
	t_model_data	*m;
	int				i;
	t_p2d			offset;

	m = model_get_real();
	slot = (num == 1) ? &m->me.key1 : NULL;
	slot = (num == 2) ? &m->me.key2 : slot;
	if (!slot || !*slot)
		return ;
	key = *slot;
	*slot = NULL;
	key->held = 0;
	key->pos = m->me.pos;
	key->respawn_ticks = 0;
	i = 0;
	offset.x = cos_deg(m->me.rot) * 0.1f;
	offset.y = sin_deg(m->me.rot) * 0.1f;
	while (i < 15)
	{
		if (model_do_collision(&key->pos, offset, 0))
			break ;
		i++;
	}
}

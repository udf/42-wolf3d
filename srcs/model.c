/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:24:21 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 10:24:49 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_model_data			*model_get_real(void)
{
	static t_model_data model_data;

	return (&model_data);
}

const t_model_data		*model_get(void)
{
	return (model_get_real());
}

int						model_init(const char *map_path)
{
	t_model_data	*m;

	m = model_get_real();
	vec_init(&m->world.cells, sizeof(t_cell), 0);
	vec_init(&m->world.doors, sizeof(t_door), 0);
	vec_init(&m->world.things, sizeof(t_thing), 0);
	return (model_map_load(map_path));
}

void					model_free(void)
{
	t_model_data	*m;

	m = model_get_real();
	vec_free(&m->world.cells);
	vec_free(&m->world.doors);
	vec_free(&m->world.things);
}

const t_cell			*model_get_cell(t_p2d pos)
{
	const t_ip2d	cpos = {(ssize_t)pos.x, (ssize_t)pos.y};
	t_world			*w;

	w = &(model_get_real()->world);
	if (cpos.x < 0 || cpos.x >= w->w)
		return (NULL);
	if (cpos.y < 0 || cpos.y >= w->h)
		return (NULL);
	return (vec_get_2d(&w->cells, (size_t)cpos.x, (size_t)cpos.y,
		(size_t)w->w));
}

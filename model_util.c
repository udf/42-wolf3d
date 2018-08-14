/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 22:45:11 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/14 22:57:31 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

const t_cell	*model_get_cell(t_p2d pos)
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

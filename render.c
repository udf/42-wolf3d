/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:34:45 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/09 18:08:08 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		render(t_env *e)
{
	const t_frange	fov_r = make_fov_range(e->me.rot, e->fov);
	int x;
	float angle;

	(void)angle;
	x = 0;
	while (x < e->w)
	{
		angle = ft_lmapf(x + 1, (t_lrange){1, e->w}, fov_r);
		//wall_cast(e, (t_ray){e->me.pos, compute_m(angle), angle}, fov_r, x);
		x++;
	}
}

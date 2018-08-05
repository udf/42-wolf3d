/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:34:45 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/05 16:53:51 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	render(t_env *e)
{
	const t_frange	fov_range = {e->me.rot - e->fov / 2, e->me.rot + e->fov / 2};
	int x;
	float theta;

	x = 0;
	while (x < e->w)
	{
		theta = ft_lmapf(x + 1, (t_lrange){1, e->w}, fov_range);
		printf("%f\n", theta);
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:55:46 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/10 15:14:23 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	copy_tex(t_env *e, t_texture *tex, int x_start, int y_start)
{
	t_pixel p;
	int x;
	int y;

	x = -1;
	while (++x < tex->w)
	{
		y = -1;
		while (++y < tex->h)
		{
			p = tex->data[x + y * tex->w];
			if (p.a == 0)
				continue;
			*buf_pixel(&e->buf, x + x_start, y + y_start) = *((Uint32*)&p);
		}
	}
}

int		ui_init(t_env *e)
{
	e->UI_tex = texture_sys_get("inventory");
	return (e->UI_tex == NULL);
}

void	ui_draw(t_env *e)
{
	copy_tex(e, e->UI_tex, 10, 10);
	if (e->me.key1)
		copy_tex(e, e->me.key1->tex, 12, 12);
	if (e->me.key2)
		copy_tex(e, e->me.key2->tex, 43, 13);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render_ui.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 22:16:48 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/14 22:20:04 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

static void	copy_tex(t_buf *buf, t_texture *tex, int x_start, int y_start)
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
			*buf_pixel(buf, x + x_start, y + y_start) = *((Uint32*)&p);
		}
	}
}

void	view_render_ui(t_view_data *v, const t_model_data *m)
{
	copy_tex(&v->buf, v->UI_tex, 10, 10);
	if (m->me.key1)
		copy_tex(&v->buf, m->me.key1->tex, 12, 12);
	if (m->me.key2)
		copy_tex(&v->buf, m->me.key2->tex, 43, 13);
}

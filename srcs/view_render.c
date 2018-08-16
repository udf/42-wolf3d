/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 19:41:24 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/15 00:08:36 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

void	view_render_bk(t_view_data *v)
{
	int x;
	int y;

	y = 0;
	while (y < v->h / 2)
	{
		x = 0;
		while (x < v->w)
		{
			*buf_pixel(&v->buf, x, y) = 0x60606060;
			x++;
		}
		y++;
	}
	while (y < v->h)
	{
		x = 0;
		while (x < v->w)
		{
			*buf_pixel(&v->buf, x, y) = 0x80808080;
			x++;
		}
		y++;
	}
}

static void		draw_column(t_view_data *v, int screen_x, t_hit hit, float dist)
{
	const float y_len = (float)v->h / dist;
	t_frange	yr;
	float	y;
	int		t_x;
	int		t_y;

	yr.s = ((float)v->h - y_len) / 2.0f - y_len * hit.v_shift;
	yr.e = ((float)v->h + y_len) / 2.0f - y_len * hit.v_shift;
	t_x = iroundf(ft_fmapf(hit.perc, (t_frange){0, 1},
		(t_frange){(float)0, (float)(hit.tex->h - 1)}));
	y = MAX(yr.s, 0);
	while (y <= MIN(yr.e, (float)v->h) - 1)
	{
		t_y = iroundf(ft_fmapf(y, yr, (t_frange){1, (float)hit.tex->h}) - 1);
		*buf_pixel(&v->buf, screen_x, iroundf(y)) =
			*((Uint32 *)&hit.tex->data[t_x + t_y * hit.tex->h]);
		y++;
	}
}

static float	ray_dist(float a, t_p2d o, t_p2d h)
{
	return (fabsf((o.x - h.x) * cos_deg(a) + (o.y - h.y) * sin_deg(a)));
}

static void		draw_cast(t_view_data *v, const t_player *me, int x, t_ray r)
{
	t_p2d	p_t;
	t_p2d	p_d;
	t_hit	hit;

	p_d = (t_p2d){modff(r.p.x, &p_t.x), modff(r.p.y, &p_t.y)};
	hit = view_raycast(r.a, p_t, p_d);
	if (!hit.valid || !hit.tex)
		return ;
	if (hit.v_shift > 0.0f) // TODO: check for texture transparency
	{
		hit.pos.x += cos_deg(r.a) * 0.0001f;
		hit.pos.y += sin_deg(r.a) * 0.0001f;
		draw_cast(v, me, x, (t_ray){hit.pos, r.a});
	}
	draw_column(v, x, hit, ray_dist(me->rot, me->pos, hit.pos));
	// TODO: draw sprites (z-buffer pls)
}

void	view_render_main(t_view_data *v, const t_model_data *m)
{
	const t_frange	fov_r = make_fov_range(m->me.rot, v->fov);
	int				x;
	t_ray			ray;

	x = 0;
	while (x < v->w)
	{
		ray.a = ft_lmapf(x + 1, (t_lrange){1, v->w}, fov_r);
		ray.p = m->me.pos;
		draw_cast(v, &m->me, x, ray);
		x++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 19:41:24 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/23 14:59:49 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

void			view_render_bk(t_view_data *v)
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
	const float	y_len = (float)v->h / dist;
	t_frange	yr;
	float		y;
	int			t_y;
	t_pixel		pix;

	yr.s = ((float)v->h - y_len) / 2.0f - y_len * hit.v_shift;
	yr.e = ((float)v->h + y_len) / 2.0f - y_len * hit.v_shift;
	y = MAX(yr.s, 0);
	while (y <= MIN(yr.e, (float)v->h) - 1)
	{
		t_y = iroundf(ft_fmapf(y, yr, (t_frange){1, (float)hit.tex->h}) - 1);
		pix = hit.tex->data[hit.tex_x + t_y * hit.tex->h];
		if (pix.a == 255)
			*buf_pixel(&v->buf, screen_x, iroundf(y)) = *((Uint32 *)&pix);
		v->z_column[iroundf(y)] = dist;
		y++;
	}
}

static int		hit_has_alpha(t_hit hit)
{
	int y;

	y = 0;
	while (y < hit.tex->h)
	{
		if (hit.tex->data[hit.tex_x + y * hit.tex->h].a != 255)
			return (1);
		y++;
	}
	return (0);
}

static void		draw_cast(t_view_data *v, const t_model_data *m, int x, t_ray r)
{
	t_p2d	p_t;
	t_p2d	p_d;
	t_hit	hit;

	p_d = (t_p2d){modff(r.p.x, &p_t.x), modff(r.p.y, &p_t.y)};
	hit = view_raycast(r.a, p_t, p_d);
	if (hit.valid && hit.tex)
	{
		if (hit.v_shift > 0.0f || hit_has_alpha(hit))
		{
			hit.pos.x += cos_deg(r.a) * 0.0001f;
			hit.pos.y += sin_deg(r.a) * 0.0001f;
			draw_cast(v, m, x, (t_ray){hit.pos, r.a});
		}
		draw_column(v, x, hit, ray_dist(m->me.rot, m->me.pos, hit.pos));
	}
	view_sprites_draw_column(v, x, r);
}

void			view_render_main(t_view_data *v, const t_model_data *m)
{
	int		x;
	int		i;
	t_ray	ray;

	v->fov_r = make_fov_range(m->me.rot, v->fov);
	view_sprites_compute(v, m);
	x = 0;
	while (x < v->w)
	{
		i = -1;
		while (++i < v->h)
			v->z_column[i] = INFINITY;
		ray.a = ft_lmapf(x + 1, (t_lrange){1, v->w}, v->fov_r);
		ray.p = m->me.pos;
		draw_cast(v, m, x, ray);
		x++;
	}
}

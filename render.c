/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:34:45 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/10 15:13:11 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	point_clip(t_p2d *p, float w, float h, t_p2d m)
{
	t_p2d	clamped;

	clamped.x = CLAMP(p->x, 0, w - 1.0f);
	if (isfinite(m.y))
		p->y = m.y * (clamped.x - p->x) + p->y;
	p->x = clamped.x;
	clamped.y = CLAMP(p->y, 0, h - 1.0f);
	if (isfinite(m.x))
		p->x = m.x * (clamped.y - p->y) + p->x;
	p->y = clamped.y;
}

int			line_clip(t_p2d *a, t_p2d *b, float w, float h)
{
	const t_p2d m = {(b->x - a->x) / (b->y - a->y),

	(b->y - a->y) / (b->x - a->x)};
	point_clip(a, w, h, m);
	point_clip(b, w, h, m);
	return ((a->x < 0 || a->x >= w || a->y < 0 || a->y >= h)
				&& (b->x < 0 || b->x >= w || b->y < 0 || b->y >= h));
}

void		img_put_line(t_env *e, t_p2d a, t_p2d b, Uint32 col)
{
	long	i;
	long	steps;
	t_p2d	p;

	if (line_clip(&a, &b, (float)e->w, (float)e->h))
		return ;
	a.x = roundf(a.x);
	a.y = roundf(a.y);
	b.x = roundf(b.x);
	b.y = roundf(b.y);
	steps = (long)MAX(ABS(b.x - a.x), ABS(b.y - a.y));
	i = 0;
	while (i < steps)
	{
		p = (t_p2d){ft_lmapf(i, (t_lrange){0, steps}, (t_frange){a.x, b.x}),
					ft_lmapf(i, (t_lrange){0, steps}, (t_frange){a.y, b.y})};
		*buf_pixel(&e->buf, (int)roundf(p.x), (int)roundf(p.y)) = col;
		i++;
	}
}

void	copy_tex(t_buf *b, t_texture *tex, int x_start, int y_start, float x_perc)
{
	const int x_t_start = (int)ft_fmapl(x_perc,
		(t_frange){0.0f, 1.0f}, (t_lrange){0, (long)tex->w});
	for (int x = x_t_start; x < tex->w; ++x)
	{
		for (int y = 0; y < tex->h; ++y)
		{
			if (x + x_start < 0 || x + x_start >= 800)
				continue;
			if (y + y_start < 0 || y + y_start >= 600)
				continue;
			t_pixel p = tex->data[x + y * tex->w];
			if (p.a == 0)
				continue;
			*buf_pixel(b, x + x_start, y + y_start) = *((Uint32*)&p);
		}
	}
}

void		render(t_env *e)
{
	const t_frange	fov_r = make_fov_range(e->me.rot, e->fov);
	t_p2d a, b;
	size_t i;
	float x, y;
	t_cell *cell;

	i = 0;
	while (i < e->world.length)
	{
		cell = vec_get(&e->world, i);
		x = (float)((int)i % (int)e->world_w);
		y = (float)((int)i / (int)e->world_w);
		if (cell->type == WALL)
			copy_tex(&e->buf, cell->wall.tex_n,
				(int)((x - e->me.pos.x) * 32 + 400),
				(int)((y - e->me.pos.y) * 32 + 300),
				0);
		if (cell->type == DOOR)
			copy_tex(&e->buf, cell->door.tex,
				(int)((x - e->me.pos.x) * 32 + 400),
				(int)((y - e->me.pos.y) * 32 + 300),
				(float)cell->door.anim_state / 100.0f);
		i++;
	}
	i = 0;
	while (i < e->world.length)
	{
		cell = vec_get(&e->world, i);
		if (cell->type == KEY)
			copy_tex(&e->buf, cell->key.tex,
				(int)((cell->key.pos.x - e->me.pos.x - 0.5f) * 32 + 400),
				(int)((cell->key.pos.y - e->me.pos.y - 0.5f) * 32 + 300),
				cell->key.held ? 1.0f : 0.0f);
		i++;
	}

	a = (t_p2d){(float)e->w / 2.0f, (float)e->h / 2.0f};
	b = (t_p2d){a.x + cos_deg(fov_r.s) * 20, a.y + sin_deg(fov_r.s) * 20};
	img_put_line(e, a, b, 0xFF000000);
	b = (t_p2d){a.x + cos_deg(fov_r.e) * 20, a.y + sin_deg(fov_r.e) * 20};
	img_put_line(e, a, b, 0xFF000000);
}

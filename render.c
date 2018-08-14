/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:34:45 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/14 17:58:34 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_p2d	to_dir(float theta)
{
	t_p2d ret;

	theta = mod_deg(theta);
	ret.x = 0;
	ret.y = 0;
	if (theta > 0 && theta < 180)
		ret.y = 1;
	else if (theta > 180 && theta < 360)
		ret.y = -1;
	if ((theta > 0 && theta < 90) || (theta > 270 && theta < 360))
		ret.x = 1;
	else if (theta > 90 && theta < 270)
		ret.x = -1;
	return (ret);
}

static t_hit	hit_test(t_env *e, t_p2d dir, t_p2d pos, char is_vert)
{
	t_cell	*cell;
	t_hit	hit;

	hit = (t_hit){NULL, {-1, -1}, fmodf(is_vert ? pos.y : pos.x, 1.0f), 0, 1};
	hit.pos = pos;
	pos.x -= (is_vert && dir.x < 0);
	pos.y -= (!is_vert && dir.y < 0);
	cell = get_cell(e, (t_ip2d){(ssize_t)pos.x, (ssize_t)pos.y});
	if (cell && cell->type == WALL)
	{
		if (is_vert)
			hit.tex = (dir.x > 0 ? cell->wall.tex_w : cell->wall.tex_e);
		else
			hit.tex = (dir.y > 0 ? cell->wall.tex_n : cell->wall.tex_s);
	}
	else if (cell && cell->type == DOOR)
	{
		hit.tex = cell->door.tex;
		hit.v_shift = (float)cell->door.anim_state / 100.0f;
	}
	else if (cell)
		hit.valid = 0;
	return (hit);
}

static t_p2d	compute_step(float theta, t_p2d dir)
{
	const float	tan_theta = fabsf(tan_deg(theta));

	return (t_p2d){dir.x * (1 / tan_theta), dir.y * tan_theta};
}

static t_p2d	compute_inter(float theta, t_p2d dir, t_p2d *p, t_p2d p_delta)
{
	float	tmp;
	t_p2d	inter;

	tmp = 0;
	if (dir.x > 0)
		tmp = 1 - p_delta.x;
	else if (dir.x < 0)
		tmp = p_delta.x;
	inter.y = p->y + p_delta.y + tmp * fabsf(tan_deg(theta)) * dir.y;
	tmp = 0;
	if (dir.y > 0)
		tmp = 1 - p_delta.y;
	else if (dir.y < 0)
		tmp = p_delta.y;
	inter.x = p->x + p_delta.x + tmp / fabsf(tan_deg(theta)) * dir.x;
	p->x += (dir.x > 0);
	p->y += (dir.y > 0);
	return (inter);
}

t_hit			do_cast(t_env *e, float theta, t_p2d p, t_p2d p_delta)
{
	const t_p2d	dir = to_dir(theta);
	const t_p2d	step = compute_step(theta, dir);
	t_p2d		inter;
	t_hit		hit;
	int safety = 0;

	SDL_SetError("params: %f, {%f, %f}, {%f, %f}\n",
		theta, p.x, p.y, p_delta.x, p_delta.y);
	inter = compute_inter(theta, dir, &p, p_delta);
	while (safety < 1000)
	{
		while ((step.y > 0 && inter.y < p.y) || (step.y < 0 && inter.y > p.y))
		{
			if ((hit = hit_test(e, dir, (t_p2d){p.x, inter.y}, 1)).valid)
				return (hit);
			p.x += dir.x;
			inter.y += step.y;
		}
		while ((step.x > 0 && inter.x < p.x) || (step.x < 0 && inter.x > p.x))
		{
			if ((hit = hit_test(e, dir, (t_p2d){inter.x, p.y}, 0)).valid)
				return (hit);
			p.y += dir.y;
			inter.x += step.x;
		}
		safety++;
	}
	// TODO: try to hit this
	printf("more than 1000 ray cast steps, wtf?\n");
	printf(SDL_GetError());
	exit(69);
	return (t_hit){NULL, {0, 0}, 0, 0, 0};
}


static void		draw_column(t_env *e, int screen_x, t_hit hit, float dist)
{
	const float y_len = (float)e->h / dist;
	t_frange	yr;
	float	y;
	int		t_x;
	int		t_y;

	yr.s = ((float)e->h - y_len) / 2.0f - y_len * hit.v_shift;
	yr.e = ((float)e->h + y_len) / 2.0f - y_len * hit.v_shift;
	t_x = iroundf(ft_fmapf(hit.perc, (t_frange){0, 1},
		(t_frange){(float)0, (float)(hit.tex->h - 1)}));
	y = MAX(yr.s, 0);
	while (y <= MIN(yr.e, (float)e->h) - 1)
	{
		t_y = iroundf(ft_fmapf(y, yr, (t_frange){1, (float)hit.tex->h}) - 1);
		*buf_pixel(&e->buf, screen_x, iroundf(y)) =
			*((Uint32 *)&hit.tex->data[t_x + t_y * hit.tex->h]);
		y++;
	}
}

static float	ray_dist(float a, t_p2d o, t_p2d h)
{
	return (fabsf((o.x - h.x) * cos_deg(a) + (o.y - h.y) * sin_deg(a)));
}

void			draw_cast(t_env *e, int screen_x, float theta, t_p2d ray_p)
{
	t_p2d	p_t;
	t_p2d	p_d;
	t_hit	hit;

	p_d = (t_p2d){modff(ray_p.x, &p_t.x), modff(ray_p.y, &p_t.y)};
	hit = do_cast(e, theta, p_t, p_d);
	if (!hit.valid || !hit.tex)
		return ;
	if (hit.v_shift > 0.0f) // TODO: check for texture transparency
	{
		hit.pos.x += cos_deg(theta) * 0.0001f;
		hit.pos.y += sin_deg(theta) * 0.0001f;
		draw_cast(e, screen_x, theta, hit.pos);
	}
	draw_column(e, screen_x, hit, ray_dist(e->me.rot, e->me.pos, hit.pos));
	// TODO: draw sprites (z-buffer pls)
}

void			render(t_env *e)
{
	const t_frange	fov_r = make_fov_range(e->me.rot, e->fov);
	int				x;

	x = 0;
	while (x < e->w)
	{
		draw_cast(e, x, ft_lmapf(x + 1, (t_lrange){1, e->w}, fov_r), e->me.pos);
		x++;
	}
}

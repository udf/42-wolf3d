/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:34:45 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/07 16:02:13 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_p2d	compute_m(float angle)
{
	const float sin_a = sin_deg(angle);
	const float cos_a = cos_deg(angle);

	return (t_p2d){cos_a / sin_a, sin_a / cos_a};
}

static void	horz_hittest(t_p2d t_p, t_ray ray, t_hit *hit)
{
	hit->p.y = t_p.y;
	hit->p.x = ray.m.x * (hit->p.y - ray.pos.y) + ray.pos.x;
	hit->x_perc = ft_fmapf(hit->p.x,
		(t_frange){t_p.x - 0.5f, t_p.x + 0.5f},
		(t_frange){0.0f, 1.0f});
	hit->dist = NAN;
	if (hit->x_perc >= 0 && hit->x_perc <= 1)
		hit->dist = p2d_dist(hit->p, ray.pos);
}

static void	vert_hittest(t_p2d t_p, t_ray ray, t_hit *hit)
{
	hit->p.x = t_p.x;
	hit->p.y = ray.m.y * (hit->p.x - ray.pos.x) + ray.pos.y;
	hit->x_perc = ft_fmapf(hit->p.y,
		(t_frange){t_p.y - 0.5f, t_p.y + 0.5f},
		(t_frange){0.0f, 1.0f});
	hit->dist = NAN;
	if (hit->x_perc >= 0 && hit->x_perc <= 1)
		hit->dist = p2d_dist(hit->p, ray.pos);
}

static int	wall_hittest(t_wall wall, t_ray ray, t_hit *hit)
{
	const t_p2d	wallp = {(float)wall.x, (float)wall.y};
	t_hit		tmp;

	hit->tex = NULL;
	hit->dist = INFINITY;
	tmp.tex = wall.tex.n;
	horz_hittest((t_p2d){wallp.x, wallp.y - 0.5f}, ray, &tmp);
	if (tmp.dist < hit->dist)
		*hit = tmp;
	tmp.tex = wall.tex.s;
	horz_hittest((t_p2d){wallp.x, wallp.y + 0.5f}, ray, &tmp);
	if (tmp.dist < hit->dist)
		*hit = tmp;
	tmp.tex = wall.tex.w;
	vert_hittest((t_p2d){wallp.x + 0.5f, wallp.y}, ray, &tmp);
	if (tmp.dist < hit->dist)
		*hit = tmp;
	tmp.tex = wall.tex.e;
	vert_hittest((t_p2d){wallp.x - 0.5f, wallp.y}, ray, &tmp);
	if (tmp.dist < hit->dist)
		*hit = tmp;
	return (hit->tex != NULL);
}

static void	draw_column(t_env *e, int x, t_hit *hit)
{
	const float	y_len = (float)e->h / hit->dist;
	const float	y_start = (float)e->h / 2.0f - (float)y_len / 2.0f;
	const float	y_end = y_start + y_len;
	int			tex_y;
	int			tex_x;
	t_pixel		pix;
	float		y;

	y = MAX(y_start, 0.0f);
	while (y <= MIN(y_end, (float)e->h - 1))
	{
		tex_y = iroundf(ft_fmapf(y, (t_frange){y_start, y_end},
					(t_frange){0.0f, (float)(hit->tex->h - 1)}));
		tex_x = iroundf(hit->x_perc * (float)(hit->tex->w - 1));
		pix = hit->tex->data[tex_x + tex_y * hit->tex->w];
		*buf_pixel(&e->buf, x, iroundf(y)) = *((Uint32 *)&pix);
		y++;
	}
}

static void	wall_cast(t_env *e, t_ray ray, t_frange fov_r, int x)
{
	size_t	i;
	t_hit	best_hit;
	t_hit	hit;
	t_wall	*walls;

	i = 0;
	walls = (t_wall *)e->walls.data;
	best_hit.tex = NULL;
	best_hit.dist = INFINITY;
	while (i < e->walls.length)
	{
		if (wall_hittest(walls[i], ray, &hit) && hit.dist < best_hit.dist)
		{
			if (is_angle_between(mod_deg(p2d_angle(ray.pos, hit.p)),
				fov_r.s, fov_r.e))
				best_hit = hit;
		}
		i++;
	}
	if (best_hit.tex != NULL)
		draw_column(e, x, &best_hit);
		// also recast walls if transparency
		// then draw sprites
	/*printf("%f* best hit at (%f,%f) %f%% %f deg %f units\n",
		ray.rot,
		best_hit.p.x, best_hit.p.y,
		best_hit.x_perc,
		p2d_angle(ray.pos, best_hit.p),
		best_hit.dist);*/
}

void		render(t_env *e)
{
	const t_frange	fov_r = make_fov_range(e->me.rot, e->fov);
	int x;
	float angle;

	x = 0;
	while (x < e->w)
	{
		angle = ft_lmapf(x + 1, (t_lrange){1, e->w}, fov_r);
		wall_cast(e, (t_ray){e->me.pos, compute_m(angle), angle}, fov_r, x);
		x++;
	}
}

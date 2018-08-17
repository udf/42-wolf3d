/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 14:16:17 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/17 13:10:43 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

static void	draw_sprite_column(t_view_data *v, int scr_x, int tex_x,
	const t_cached_sprite *spr)
{
	const float	y_len = (float)v->h / spr->dist;
	int			tex_y;
	t_frange	yr;
	float		y;
	t_pixel		pix;

	yr.e = ((float)v->h + y_len) / 2.0f;
	yr.s = yr.e - y_len * spr->scale;
	y = MAX(yr.s, 0);
	while (y <= MIN(yr.e, (float)v->h) - 1)
	{
		tex_y = iroundf(ft_fmapf(y, yr, (t_frange){1, (float)spr->tex->h}) - 1);
		pix = spr->tex->data[tex_x + tex_y * spr->tex->w];
		if (pix.a && v->z_column[iroundf(y)] > spr->dist)
		{
			*buf_pixel(&v->buf, scr_x, iroundf(y)) = *((Uint32 *)&pix);
			v->z_column[iroundf(y)] = spr->dist;
		}
		y++;
	}
}

void		view_sprites_draw_column(t_view_data *v, int scr_x, t_ray ray)
{
	size_t			i;
	t_cached_sprite	*sprite;
	float			tmp_a;
	int				tex_x;

	i = 0;
	ray.a = fmodf(ray.a, 360.0f);
	while (i < v->sprite_cache.length)
	{
		sprite = vec_get(&v->sprite_cache, i);
		tmp_a = ray.a;
		while (tmp_a < sprite->ar.s)
			tmp_a += 360.0f;
		if (sprite->tex && is_angle_between(ray.a, sprite->ar))
		{
			tex_x = iroundf(ft_fmapf(tmp_a, sprite->ar,
				(t_frange){1, (float)sprite->tex->w}) - 1);
			draw_sprite_column(v, scr_x, tex_x, sprite);
		}
		i++;
	}
}

void	view_sprites_compute(t_view_data *v, const t_model_data *m)
{
	size_t			i;
	t_thing			*thing;
	t_cached_sprite	cache;

	i = 0;
	v->sprite_cache.length = 0;
	while (i < m->world.things.length)
	{
		thing = vec_get((t_vec *)&m->world.things, i);
		cache.tex = NULL;
		cache.scale = 1;
		if (thing->type == KEY && !thing->key.held)
		{
			cache.scale = 0.25f;
			cache.tex = thing->key.tex;
		}
		else if (thing->type == PROP)
			cache.tex = thing->prop.tex;
		cache.dist = p2d_dist(m->me.pos, thing->prop.pos);
		cache.ar = make_fov_range(p2d_angle(m->me.pos, thing->prop.pos),
			v->fov / cache.dist * cache.scale);
		vec_append(&v->sprite_cache, &cache);
		i++;
	}
}

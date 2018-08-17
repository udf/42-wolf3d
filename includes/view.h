/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:24:11 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/17 22:05:46 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "libft.h"
# include "SDL.h"
# include "util.h"
# include "model.h"

# define VAL_CLOSE(v1, v2) (fabsf(v1 - v2) <= 0.00001f)
# define VAL_CAN_MOVE(v, s, a) ((s >= 0 && v <= a) || (s <= 0 && v >= a))

typedef struct		s_hit
{
	t_texture		*tex;
	t_p2d			pos;
	float			perc;
	float			v_shift;
	char			valid;
}					t_hit;

typedef struct		s_ray
{
	t_p2d			p;
	float			a;
}					t_ray;

typedef struct		s_buf
{
	SDL_Texture		*tex;
	Uint32			*pixels;
	int				pitch;
}					t_buf;

typedef struct		s_cached_sprite
{
	t_texture		*tex;
	t_frange		ar;
	t_p2d			scale;
	float			dist;
	char			flip_x;
}					t_cached_sprite;

typedef struct		s_view_data
{
	t_vec			sprite_cache;
	t_buf			buf;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_texture		*ui_tex;
	t_frange		fov_r;
	int				w;
	int				h;
	float			fov;
	float			*z_column;
}					t_view_data;

/*
** Public
*/
int					view_init(int w, int h, float fov);
void				view_free(void);
void				view_update(void);

/*
** Private
*/
void				view_render_bk(t_view_data *v);
void				view_render_main(t_view_data *v, const t_model_data *m);
void				view_render_ui(t_view_data *v, const t_model_data *m);
t_hit				view_raycast(float theta, t_p2d p, t_p2d p_delta);
void				view_sprites_compute(t_view_data *v, const t_model_data *m);
void				view_sprites_draw_column(t_view_data *v, int x, t_ray ray);

/*
** Utility
*/
int					iroundf(float v);
t_frange			make_fov_range(float rot, float fov);
Uint32				*buf_pixel(t_buf *buf, int x, int y);
float				ray_dist(float a, t_p2d o, t_p2d h);

#endif

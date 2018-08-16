/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:24:11 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 10:19:18 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "libft.h"
# include "SDL.h"
# include "util.h"
# include "model.h"

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

typedef struct		s_view_data
{
	int				w;
	int				h;
	float			fov;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_texture		*UI_tex;
	t_buf			buf;
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

/*
** Utility
*/
int					iroundf(float v);
t_frange			make_fov_range(float rot, float fov);
Uint32				*buf_pixel(t_buf *buf, int x, int y);

#endif

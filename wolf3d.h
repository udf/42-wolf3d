/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/07 15:59:45 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"
# include "vec.h"

# include "texture_sys.h"

# include <stdio.h>

typedef struct		s_p2d
{
	float			x;
	float			y;
}					t_p2d;

typedef struct		s_ip2d
{
	ssize_t			x;
	ssize_t			y;
}					t_ip2d;

typedef struct		s_player
{
	t_p2d			pos;
	float			rot;
}					t_player;

typedef struct		s_walltex
{
	t_texture		*n;
	t_texture		*s;
	t_texture		*e;
	t_texture		*w;
}					t_walltex;

typedef struct		s_wall
{
	int				x;
	int				y;
	t_walltex		tex;
}					t_wall;

typedef struct		s_door
{
	int				x;
	int				y;
	t_texture		*tex;
}					t_door;

typedef struct		s_key
{
	int				x;
	int				y;
	t_texture		*tex;
	char			held;
}					t_key;

typedef struct		s_sprite
{
	int				x;
	int				y;
	t_texture		*tex;
}					t_sprite;

typedef struct		s_hit
{
	t_p2d			p;
	float			x_perc;
	float			dist;
	t_texture		*tex;
}					t_hit;

typedef struct		s_ray
{
	t_p2d			pos;
	t_p2d			m;
	float			rot;
}					t_ray;

typedef struct		s_buf
{
	SDL_Texture		*tex;
	Uint32			*pixels;
	int				pitch;
}					t_buf;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_buf			buf;
	int				w;
	int				h;
	float			fov;
	t_player		me;
	t_vec			walls;
	t_vec			doors;
	t_vec			keys;
	t_vec			sprites;
}					t_env;

int				load_map(t_env *e, const char *path);

void			render(t_env *e);

size_t			seek_token(char **str);
void			set_draw_colour(SDL_Renderer *ren, Uint32 col);
int				iroundf(float v);
float			mod_deg(float deg);
t_frange		make_fov_range(float rot, float fov);
int				is_angle_between(float a, float start, float end);
Uint32			*buf_pixel(t_buf *buf, int x, int y);

float			sin_deg(float deg);
float			cos_deg(float deg);
float			tan_deg(float deg);
float			p2d_dist(t_p2d a, t_p2d b);
float			p2d_angle(t_p2d a, t_p2d b);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/10 15:10:48 by mhoosen          ###   ########.fr       */
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

# include "world.h"

typedef struct		s_player
{
	t_p2d			pos;
	float			rot;
	t_ip2d			touched_cell;
	t_cell_key		*key1;
	t_cell_key		*key2;
	char			exit;
}					t_player;

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
	t_texture		*UI_tex;
	t_buf			buf;
	int				w;
	int				h;
	float			fov;
	t_player		me;
	t_vec			world;
	ssize_t			world_w;
	ssize_t			world_h;
}					t_env;

int				load_map(t_env *e, const char *path);
void			process_player_token(t_cell *cell, char c, t_env *e, t_ip2d p);
void			process_wall_token(t_cell *cell, char c);
void			process_door_token(t_cell *cell, char c);
void			process_key_token(t_cell *cell, char c, t_ip2d pos);
void			process_prop_token(t_cell *cell, char c);

void			render(t_env *e);
int				ui_init(t_env *e);
void			ui_draw(t_env *e);

size_t			seek_token(char **str);
Uint32			*buf_pixel(t_buf *buf, int x, int y);
int				iroundf(float v);
float			mod_deg(float deg);
t_frange		make_fov_range(float rot, float fov);
int				is_angle_between(float a, float start, float end); // TODO: check usage
t_cell			*get_cell(t_env *e, t_ip2d cpos);

float			sin_deg(float deg);
float			cos_deg(float deg);
float			tan_deg(float deg);
float			p2d_dist(t_p2d a, t_p2d b); // TODO: check usage
float			p2d_angle(t_p2d a, t_p2d b); // TODO: check usage

void			process_collision(t_env *e, t_p2d *target, t_p2d offset);
void			process_logic(t_env *e, ssize_t ticks);


#endif

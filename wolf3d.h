/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/05 16:44:17 by mhoosen          ###   ########.fr       */
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
	SDL_Surface		*n;
	SDL_Surface		*s;
	SDL_Surface		*e;
	SDL_Surface		*w;
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
	SDL_Surface		*tex;
}					t_door;

typedef struct		s_key
{
	int				x;
	int				y;
	SDL_Surface		*tex;
	char			held;
}					t_key;

typedef struct		s_sprite
{
	int				x;
	int				y;
	SDL_Surface		*tex;
}					t_sprite;

typedef struct		s_world
{
	t_vec			walls;
	t_vec			doors;
	t_vec			keys;
	t_vec			sprites;
}					t_world;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	int				w;
	int				h;
	float			fov;
	t_player		me;
	t_world			world;
}					t_env;

int				load_map(t_env *e, const char *path);

size_t			seek_token(char **str);
void			set_draw_colour(SDL_Renderer *ren, Uint32 col);

float			sin_deg(float deg);
float			cos_deg(float deg);
float			tan_deg(float deg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:24:11 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 21:11:03 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_H
# define MODEL_H

# include <fcntl.h>

# include "SDL.h"
# include "texture_sys.h"
# include "get_next_line.h"
# include "vec.h"
# include "util.h"

/*
** World cells
*/
typedef struct		s_wall
{
	t_texture		*tex_n;
	t_texture		*tex_s;
	t_texture		*tex_e;
	t_texture		*tex_w;
}					t_wall;

typedef struct		s_door
{
	t_texture		*tex;
	short			open_ticks;
	char			anim_state;
	char			colour;
}					t_door;

typedef enum		e_cell
{
	EMPTY,
	WALL,
	DOOR
}					t_e_cell;

typedef struct		s_cell
{
	t_e_cell		type;
	union
	{
		t_wall		*wall;
		t_door		*door;
	};
}					t_cell;

/*
** Things
*/
typedef struct		s_key
{
	t_texture		*tex;
	t_p2d			pos;
	short			respawn_ticks;
	char			held;
	char			colour;
}					t_key;

typedef struct		s_prop
{
	t_texture		*tex;
	t_p2d			pos;
}					t_prop;

typedef enum		e_thing
{
	KEY,
	PROP
}					t_e_thing;

typedef struct		s_thing
{
	t_e_thing		type;
	union
	{
		t_key		key;
		t_prop		prop;
	};
}					t_thing;

typedef struct		s_world
{
	ssize_t			w;
	ssize_t			h;
	t_vec			cells;
	t_wall			walls[256];
	t_vec			doors;
	t_vec			things;
}					t_world;

typedef struct		s_player
{
	t_p2d			pos;
	float			rot;
	t_key			*key1;
	t_key			*key2;
}					t_player;

typedef struct		s_model_data
{
	t_player		me;
	t_world			world;
}					t_model_data;

/*
** Public
*/
const t_model_data	*model_get(void);
int					model_init(const char *map_path);
void				model_free(void);
void				model_update(ssize_t elapsed_ticks, float elapsed_secs);

void				model_player_move(float amount);
void				model_player_rotate(float amount);
void				model_player_drop_key(int num);

int					model_do_collision(t_p2d *target, t_p2d offset);
const t_cell		*model_get_cell(t_p2d pos);

/*
** Private
*/
t_model_data		*model_get_real(void);
int					model_map_load(const char *map_path);
int					process_player_token(t_player *me, char c, t_ip2d pos);
int					process_wall_token(t_cell *cell, t_wall walls[256], char c);
int					process_door_token(t_cell *cell, t_vec *doors, char c);
int					process_key_token(t_vec *things, char c, t_ip2d pos);
int					process_prop_token(t_vec *things, char c, t_ip2d pos);

#endif

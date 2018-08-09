/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:58:10 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/09 21:34:16 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "texture_sys.h"

/*
** Enumeration of cell types
*/
enum					e_cell
{
	UNKNOWN,
	EMPTY,
	WALL,
	DOOR,
	KEY,
	PROP
};

/*
** A wall, contains 4 textures for each direction
*/
typedef struct			s_cell_wall
{
	t_texture			*tex_n;
	t_texture			*tex_s;
	t_texture			*tex_e;
	t_texture			*tex_w;
}						t_cell_wall;

/*
** A door
** open_ticks: how many ticks the door should remain open for
** anim_state: 0-100, how far open the door is
** colour: A key with the same colour can be used to open the door
*/
typedef struct			s_cell_door
{
	t_texture			*tex;
	short				open_ticks;
	char				anim_state;
	char				colour;
}						t_cell_door;

/*
** A key that can be picked up and used to open a matching door
** respawn_ticks: how long until the held value is set to 0
**     held is only reset when this value crosses 0
** held: if a key is held by the player or not
** colour: The colour of door that this key can open
** x, y: position of the key
*/
typedef struct			s_cell_key
{
	t_texture			*tex;
	short				respawn_ticks;
	char				held;
	char				colour;
	float				x;
	float				y;
}						t_cell_key;

/*
** A decoration, does nothing and can't be interacted with
*/
typedef struct			s_cell_prop
{
	t_texture			*tex;
}						t_cell_prop;

typedef struct			s_cell
{
	enum e_cell type;
	union
	{
		t_cell_wall		wall;
		t_cell_door		door;
		t_cell_key		key;
		t_cell_prop		prop;
	};
}						t_cell;

#endif

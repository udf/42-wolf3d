/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/04 01:52:51 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "SDL.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"
# include "vec.h"

# include <stdio.h>

/*
** Your standard 2D point
*/
typedef struct		s_p2d
{
	float			x;
	float			y;
}					t_p2d;

typedef struct		s_player
{
	t_p2d			pos;
	float			rot;
}					t_player;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_player		me;
}					t_env;

float			sin_deg(float deg);
float			cos_deg(float deg);

#endif

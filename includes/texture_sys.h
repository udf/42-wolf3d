/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sys.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 23:56:56 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/23 15:03:24 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_SYS_H
# define TEXTURE_SYS_H

# include "SDL.h"
# include "libft.h"
# include "vec.h"

typedef struct	s_pixel
{
	Uint8		a;
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_pixel;

typedef struct	s_texture
{
	t_pixel		*data;
	int			w;
	int			h;
}				t_texture;

typedef struct	s_loaded_texture
{
	char		filename[16];
	t_texture	*texture;
}				t_loaded_texture;

t_texture		*texture_sys_get(char *filename);
void			texture_sys_free();
Uint32			surface_get_pixel(SDL_Surface *surface, int x, int y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sys.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 23:56:56 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/05 00:29:50 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_SYS_H
# define TEXTURE_SYS_H

# include "SDL.h"
# include "libft.h"
# include "vec.h"
# include <stdio.h>

/*
** texsys sounds like texas
*/
# define TEXAS_GET 0
# define TEXAS_FREE 1

typedef struct		s_tex
{
	char			filename[16];
	SDL_Surface		*texture;
}					t_tex;

SDL_Surface			*texture_sys(int func, char *filename);

#endif

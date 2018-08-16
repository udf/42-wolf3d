/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sys_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 10:40:42 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 10:40:58 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_sys.h"

Uint32		surface_get_pixel(SDL_Surface *surface, int x, int y)
{
	const int	bpp = surface->format->BytesPerPixel;
	const Uint8	*p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	if (bpp == 1)
		return (*p);
	if (bpp == 2)
		return (*(Uint16 *)p);
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return ((Uint32)(p[0] << 16 | p[1] << 8 | p[2]));
		else
			return ((Uint32)(p[0] | p[1] << 8 | p[2] << 16));
	}
	if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}

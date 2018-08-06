/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 13:52:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/06 11:45:47 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

size_t	seek_token(char **str)
{
	char	*iter;
	size_t		tok_len;

	iter = *str;
	while (iter && *iter && *iter == ' ')
		iter++;
	tok_len = 0;
	*str = iter;
	while (iter && iter[tok_len] && iter[tok_len] != ' ')
		tok_len++;
	return (tok_len);
}

int		iroundf(float v)
{
	return ((int)roundf(v));
}

float	mod_deg(float deg)
{
	return (fmodf(deg + 360.0f, 360.0f));
}

t_frange	make_fov_range(float rot, float fov)
{
	t_frange r;

	r = (t_frange){mod_deg(rot - fov / 2), mod_deg(rot + fov / 2)};
	if (r.e < r.s)
		r.e += 360.0f;
	return (r);
}

int		is_angle_between(float a, float start, float end)
{
	a += a < start ? 360.0f : 0;
	return (a >= start && a <= end);
}

void	set_draw_colour(SDL_Renderer *ren, Uint32 col)
{
	SDL_SetRenderDrawColor(ren,
		(col >> 16) & 0xFF, (col >> 8) & 0xFF, col & 0xFF, 0xFF);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 13:52:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/10 09:35:07 by mhoosen          ###   ########.fr       */
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

Uint32	*buf_pixel(t_buf *buf, int x, int y)
{
	const int pitch = buf->pitch / (int)sizeof(Uint32);

	return (&buf->pixels[x + pitch * y]);
}

t_cell	*get_cell(t_env *e, t_ip2d cpos)
{
	if (cpos.x < 0 || cpos.x >= e->world_w)
		return (NULL);
	if (cpos.y < 0 || cpos.y >= e->world_h)
		return (NULL);
	return (vec_get_2d(&e->world, (size_t)cpos.x, (size_t)cpos.y,
		(size_t)e->world_w));
}

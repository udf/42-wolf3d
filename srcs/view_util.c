/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 19:44:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/14 22:12:37 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

int		iroundf(float v)
{
	return ((int)roundf(v));
}

t_frange	make_fov_range(float rot, float fov)
{
	t_frange r;

	r = (t_frange){mod_deg(rot - fov / 2), mod_deg(rot + fov / 2)};
	if (r.e < r.s)
		r.e += 360.0f;
	return (r);
}

Uint32	*buf_pixel(t_buf *buf, int x, int y)
{
	const int pitch = buf->pitch / (int)sizeof(Uint32);

	return (&buf->pixels[x + pitch * y]);
}

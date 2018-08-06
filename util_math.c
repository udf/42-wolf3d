/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 02:00:32 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/05 18:43:09 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	sin_deg(float deg)
{
	const float pi_over_180 = (float)(M_PI / 180.0);

	return (sinf(deg * pi_over_180));
}

float	cos_deg(float deg)
{
	const float pi_over_180 = (float)(M_PI / 180.0);

	return (cosf(deg * pi_over_180));
}

float	tan_deg(float deg)
{
	const float pi_over_180 = (float)(M_PI / 180.0);

	return (tanf(deg * pi_over_180));
}

float	p2d_dist(t_p2d a, t_p2d b)
{
	const float dx = a.x - b.x;
	const float dy = a.y - b.y;

	return (sqrtf(dx * dx + dy * dy));
}

float	p2d_angle(t_p2d a, t_p2d b)
{
	const float pi_over_180_r = (float)(180.0 / M_PI);

	return (atan2f(b.y - a.y, b.x - a.x) * pi_over_180_r);
}

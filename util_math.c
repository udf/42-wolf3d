/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 02:00:32 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/04 02:00:58 by mhoosen          ###   ########.fr       */
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

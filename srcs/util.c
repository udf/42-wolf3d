/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 22:10:04 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 10:22:35 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

float	mod_deg(float deg)
{
	const float n = 360.0f;

	return (fmodf(fmodf(deg, n) + n, n));
}

int		is_angle_between(float a, float start, float end)
{
	a += a < start ? 360.0f : 0;
	return (a >= start && a <= end);
}

void	post_exit_event(void)
{
	SDL_Event event;

	event.type = SDL_QUIT;
	event.quit.timestamp = 0;
	SDL_PushEvent(&event);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 22:10:04 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 12:46:45 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

float	mod_deg(float deg)
{
	const float n = 360.0f;

	return (fmodf(fmodf(deg, n) + n, n));
}

int		is_angle_between(float a, t_frange range)
{
	while (a < range.s)
		a += 360.0f;
	return (a >= range.s && a <= range.e);
}

void	post_exit_event(void)
{
	SDL_Event event;

	event.type = SDL_QUIT;
	event.quit.timestamp = 0;
	SDL_PushEvent(&event);
}

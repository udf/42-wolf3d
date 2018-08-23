/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:24:21 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/23 16:25:31 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static void	process_input(float secs)
{
	const Uint8			*state = SDL_GetKeyboardState(NULL);
	float				dir;

	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])
	{
		dir = 2.0f * secs;
		if (state[SDL_SCANCODE_DOWN])
			dir *= -1.0f;
		model_player_move(dir);
	}
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
	{
		dir = 1.0f;
		if (state[SDL_SCANCODE_LEFT])
			dir *= -1.0f;
		model_player_rotate(secs * dir * 90.f);
	}
}

int			controller_process_events(float elapsed_secs)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
			(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
			return (1);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_Z)
				model_player_drop_key(1);
			else if (event.key.keysym.scancode == SDL_SCANCODE_X)
				model_player_drop_key(2);
		}
	}
	process_input(elapsed_secs);
	return (0);
}

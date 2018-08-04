/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:27:49 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/04 02:14:17 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	die(t_env *e, int code, char *pre_msg)
{
	if (code)
	{
		ft_putstr_fd(pre_msg, 2);
		ft_putendl_fd(SDL_GetError(), 2);
	}
	SDL_DestroyRenderer(e->ren);
	SDL_DestroyWindow(e->win);
	SDL_Quit();
	exit(code);
}

void	draw(t_env *e)
{
	SDL_SetRenderDrawColor(e->ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(e->ren);
	SDL_SetRenderDrawColor(e->ren, 0xFF, 0x00, 0x00, 0x00);
	SDL_RenderDrawPoint(e->ren, 10, 10);
	SDL_RenderPresent(e->ren);
}

int		process_event(SDL_Event *ev)
{
	if (ev->type == SDL_KEYUP)
	{
		if (ev->key.keysym.sym == SDLK_ESCAPE)
			return (1);
	}
	return (0);
}

void	process_input(t_env *e, float secs)
{
	const Uint8	*state = SDL_GetKeyboardState(NULL);
	float		direction;

	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])
	{
		direction = 1.0f;
		if (state[SDL_SCANCODE_DOWN])
			direction *= -1.0f;
		e->me.pos.x += sin_deg(e->me.rot) * secs * direction;
		e->me.pos.y += cos_deg(e->me.rot) * secs * direction;
	}
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
	{
		direction = 1.0f;
		if (state[SDL_SCANCODE_LEFT])
			direction *= -1.0f;
		e->me.rot += secs * direction * 90.f;
	}
	printf("%f %f (%f)\n", e->me.pos.x, e->me.pos.y, e->me.rot);
}

void	loop(t_env *e)
{
	SDL_Event	event;
	Uint32		last_ticks;

	last_ticks = SDL_GetTicks();
	while (1)
	{
		while (SDL_PollEvent(&event))
			if (process_event(&event))
				return ;
		draw(e);
		process_input(e, (float)(SDL_GetTicks() - last_ticks) / 1000.0f);
		last_ticks = SDL_GetTicks();
	}
}

int	main(void)
{
	static t_env e;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		die(&e, 1, "Failed to initialize SDL: ");
	e.win = SDL_CreateWindow("wolf3d",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (!e.win)
		die(&e, 1, "Failed to create window: ");
	e.ren = SDL_CreateRenderer(e.win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!e.ren)
		die(&e, 1, "Failed to create renderer: ");
	loop(&e);
	die(&e, 0, 0);
	return 0;
}

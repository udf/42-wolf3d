/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:27:49 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/07 16:28:52 by mhoosen          ###   ########.fr       */
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
	vec_free(&e->walls);
	vec_free(&e->doors);
	vec_free(&e->keys);
	vec_free(&e->sprites);
	texture_sys(TEXAS_FREE, NULL);
	SDL_DestroyTexture(e->buf.tex);
	SDL_DestroyRenderer(e->ren);
	SDL_DestroyWindow(e->win);
	SDL_Quit();
	exit(code);
}

void	draw_background(t_env *e)
{
	const Uint32	upper = 0x60606060;
	const Uint32	lower = 0x80808080;
	int x;
	int y;

	y = 0;
	while (y < e->h)
	{
		x = 0;
		while (x < e->w)
		{
			*buf_pixel(&e->buf, x, y) = (y < e->h / 2 ? upper : lower);
			x++;
		}
		y++;
	}
}

void	draw(t_env *e)
{
	SDL_LockTexture(e->buf.tex, NULL, (void **)&e->buf.pixels, &e->buf.pitch);
	SDL_RenderClear(e->ren);
	draw_background(e);

	render(e);

	SDL_UnlockTexture(e->buf.tex);
	SDL_RenderCopy(e->ren, e->buf.tex, NULL, NULL);
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
		e->me.pos.x += cos_deg(e->me.rot) * secs * direction;
		e->me.pos.y += sin_deg(e->me.rot) * secs * direction;
	}
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
	{
		direction = 1.0f;
		if (state[SDL_SCANCODE_LEFT])
			direction *= -1.0f;
		e->me.rot += secs * direction * 90.f;
		e->me.rot = mod_deg(e->me.rot);
	}
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

void	init_vectors(t_env *e)
{
	vec_init(&e->walls, sizeof(t_wall), 0);
	vec_init(&e->doors, sizeof(t_door), 0);
	vec_init(&e->keys, sizeof(t_key), 0);
	vec_init(&e->sprites, sizeof(t_sprite), 0);
}

int	main(int ac, char **av)
{
	static t_env e;

	if (ac <= 1)
		die(&e, 1, "No map file provided");
	init_vectors(&e);
	if (load_map(&e, av[1]))
		die(&e, 1, NULL);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		die(&e, 1, "Failed to initialize SDL: ");
	e.w = 800;
	e.h = 600;
	e.fov = 75.0f;
	e.win = SDL_CreateWindow("wolf3d",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, e.w, e.h, 0);
	if (!e.win)
		die(&e, 1, "Failed to create window: ");
	e.ren = SDL_CreateRenderer(e.win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!e.ren)
		die(&e, 1, "Failed to create renderer: ");
	e.buf.tex = SDL_CreateTexture(e.ren, SDL_PIXELFORMAT_ARGB32,
		SDL_TEXTUREACCESS_STREAMING, e.w, e.h);
	if (!e.buf.tex)
		die(&e, 1, "Failed to create texture: ");
	loop(&e);
	die(&e, 0, "Thanks for playing");
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:46:12 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 10:22:50 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	die(int code, char *pre_msg)
{
	if (pre_msg)
		ft_putstr_fd(pre_msg, 2);
	if (code)
		ft_putendl_fd(SDL_GetError(), 2);
	view_free();
	model_free();
	texture_sys_free();
	SDL_Quit();
	exit(code);
}

static void	loop(void)
{
	Uint32		last_ticks;
	ssize_t		elapsed_ticks;
	float		elapsed_secs;

	last_ticks = SDL_GetTicks();
	while (1)
	{
		elapsed_ticks = SDL_GetTicks() - last_ticks;
		last_ticks = SDL_GetTicks();
		elapsed_secs = (float)elapsed_ticks / 1000.0f;
		if (controller_process_events(elapsed_secs))
			break ;
		model_update(elapsed_ticks, elapsed_secs);
		view_update();
	}
}

int			main(int ac, char **av)
{
	if (ac <= 1)
		die(1, "No map file provided");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		die(2, "Failed to initialize SDL: ");
	if (model_init(av[1]))
		die(3, NULL);
	if (view_init(800, 600, 75.0f))
		die(4, NULL);
	loop();
	die(0, "Thanks for playing!\n");
	return (0);
}

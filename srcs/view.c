/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:24:21 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 10:42:51 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

static t_view_data	*view_get(void)
{
	static t_view_data view_data;

	return (&view_data);
}

int					view_init(int w, int h, float fov)
{
	t_view_data *v;

	v = view_get();
	v->w = w;
	v->h = h;
	v->fov = fov;
	v->win = SDL_CreateWindow("wolf3d",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (!v->win)
		return (1);
	v->ren = SDL_CreateRenderer(v->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!v->ren)
		return (1);
	v->buf.tex = SDL_CreateTexture(v->ren, SDL_PIXELFORMAT_ARGB32,
		SDL_TEXTUREACCESS_STREAMING, w, h);
	if (!v->buf.tex)
		return (1);
	if (!(v->ui_tex = texture_sys_get("inventory")))
		return (1);
	return (0);
}

void				view_free(void)
{
	t_view_data *v;

	v = view_get();
	SDL_DestroyTexture(v->buf.tex);
	SDL_DestroyRenderer(v->ren);
	SDL_DestroyWindow(v->win);
}

void				view_update(void)
{
	const t_model_data	*m = model_get();
	t_view_data			*v;

	v = view_get();
	SDL_LockTexture(v->buf.tex, NULL, (void **)&v->buf.pixels, &v->buf.pitch);
	SDL_RenderClear(v->ren);
	view_render_bk(v);
	view_render_main(v, m);
	view_render_ui(v, m);
	SDL_UnlockTexture(v->buf.tex);
	SDL_RenderCopy(v->ren, v->buf.tex, NULL, NULL);
	SDL_RenderPresent(v->ren);
}

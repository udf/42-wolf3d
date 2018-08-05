/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 00:03:33 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/05 16:12:27 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_sys.h"

static SDL_Surface	*texture_sys_get(t_vec *texas, char *filename)
{
	char		path[128];
	size_t		i;
	t_tex		*textures;
	t_tex		ret;

	i = 0;
	textures = (t_tex *)texas->data;
	while (i < texas->length)
	{
		if (ft_strncmp(textures[i].filename, filename, 16) == 0)
			return (textures[i].texture);
		i++;
	}
	ft_bzero(ret.filename, 16);
	ft_strncat(ret.filename, filename, 15);
	ft_bzero(path, 128);
	ft_strncat(path, "assets/", 127);
	ft_strncat(path, ret.filename, 127);
	ft_strncat(path, ".bmp", 127);
	printf("texas: Loading %s from %s\n", ret.filename, path);
	ret.texture = SDL_LoadBMP(path);
	SDL_LockSurface(ret.texture);
	if (ret.texture)
		vec_append(texas, &ret);
	return (ret.texture);
}

static SDL_Surface	*texture_sys_free(t_vec *texas)
{
	size_t		i;
	t_tex		*textures;
	i = 0;

	textures = (t_tex *)texas->data;
	while (i < texas->length)
	{
		SDL_UnlockSurface(textures[i].texture);
		SDL_FreeSurface(textures[i].texture);
		i++;
	}
	vec_free(texas);
	return (NULL);
}

SDL_Surface			*texture_sys(int func, char *filename)
{
	static t_vec	textures;

	if (textures.type_size == 0)
		vec_init(&textures, sizeof(t_tex), 0);
	if (func == TEXAS_GET)
		return (texture_sys_get(&textures, filename));
	if (func == TEXAS_FREE)
		return (texture_sys_free(&textures));
	SDL_SetError("Texture system: unknown function");
	return (NULL);
}

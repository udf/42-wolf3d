/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 00:03:33 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/23 15:05:42 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_sys.h"

static t_vec		*get_vec(void)
{
	static t_vec	textures;

	if (textures.type_size == 0)
		vec_init(&textures, sizeof(t_loaded_texture), 0);
	return (&textures);
}

static void			surface_to_tex(SDL_Surface *surface, t_texture *tex)
{
	int			x;
	int			y;
	Uint32		pixel;
	int			i;

	y = 0;
	tex->w = surface->w;
	tex->h = surface->h;
	tex->data = ft_memalloc((size_t)tex->w * (size_t)tex->h * sizeof(t_pixel));
	if (!tex->data)
		return ;
	while (y < surface->h)
	{
		x = 0;
		while (x < surface->w)
		{
			i = x + y * tex->w;
			pixel = surface_get_pixel(surface, x, y);
			SDL_GetRGBA(pixel, surface->format, &tex->data[i].r,
				&tex->data[i].g, &tex->data[i].b, &tex->data[i].a);
			x++;
		}
		y++;
	}
}

static t_texture	*load_bmp(char *path)
{
	SDL_Surface	*surface;
	t_texture	*tex;

	if (!(surface = SDL_LoadBMP(path)))
		return (NULL);
	SDL_LockSurface(surface);
	tex = ft_memalloc(sizeof(t_texture));
	surface_to_tex(surface, tex);
	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
	if (!tex->data)
		ft_memdel((void **)&tex);
	return (tex);
}

t_texture			*texture_sys_get(char *filename)
{
	char				path[128];
	size_t				i;
	t_loaded_texture	*textures;
	t_loaded_texture	ret;

	i = 0;
	textures = (t_loaded_texture *)get_vec()->data;
	while (i < get_vec()->length)
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
	ret.texture = load_bmp(path);
	if (ret.texture)
		vec_append(get_vec(), &ret);
	return (ret.texture);
}

void				texture_sys_free(void)
{
	size_t				i;
	t_loaded_texture	*textures;

	i = 0;
	textures = (t_loaded_texture *)(get_vec()->data);
	while (i < get_vec()->length)
	{
		free(textures[i].texture->data);
		free(textures[i].texture);
		i++;
	}
	vec_free(get_vec());
}

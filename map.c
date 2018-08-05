/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:39:34 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/05 16:32:25 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
/*
@s
^

blank
_

door
Db
Dg
Dr
Dy

key
Kb
Kg
Kr
Ky

prop
Pc
Pe
Pp
Ps

wall
W1
*/

static int	get_wall_tex(char prefix, t_walltex *out)
{
	static char	tmp_name[8];

	tmp_name[0] = 'W';
	tmp_name[1] = prefix;
	tmp_name[2] = 'n';
	if (!(out->n = texture_sys(TEXAS_GET, tmp_name)))
		return (1);
	tmp_name[2] = 's';
	if (!(out->s = texture_sys(TEXAS_GET, tmp_name)))
		return (1);
	tmp_name[2] = 'e';
	if (!(out->e = texture_sys(TEXAS_GET, tmp_name)))
		return (1);
	tmp_name[2] = 'w';
	if (!(out->w = texture_sys(TEXAS_GET, tmp_name)))
		return (1);
	return (0);
}

static int	process_token(t_env *e, const char *str, size_t len, t_ip2d pos)
{
	t_wall	tmp_wall;

	if (*str == 'W' && len == 2)
	{
		tmp_wall.x = (int)pos.x;
		tmp_wall.y = (int)pos.y;
		if (get_wall_tex(str[1], &tmp_wall.tex))
			return (1);
		vec_append(&e->world.walls, &tmp_wall);
		return (0);
	}
	if (*str == '@' && len == 2)
	{
		e->me.pos = (t_p2d){(float)pos.x, (float)pos.y};
		e->me.rot = -1.0f;
		if (str[1] == 'e')
			e->me.rot = 0.0f;
		if (str[1] == 's')
			e->me.rot = 90.0f;
		if (str[1] == 'w')
			e->me.rot = 180.0f;
		if (str[1] == 'n')
			e->me.rot = 270.0f;
		if (e->me.rot != -1.0f)
			return (0);
	}
	if (ft_strncmp(str, "_", 1) == 0)
		return (0);
	SDL_SetError("Unknown token \"%.*s\": line %zd, token %zd",
		(int)len, str, pos.y + 1, pos.x + 1);
	return (1);
}

int			load_map(t_env *e, const char *path)
{
	int		fd;
	char	*line;
	char	*iter;
	size_t	tok_len;
	t_ip2d	pos;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (SDL_SetError("Could not open map file"));
	pos.y = 0;
	while (get_next_line(fd, &line) == GNL_SUCCESS)
	{
		iter = line;
		pos.x = 0;
		while ((tok_len = seek_token(&iter)) > 0)
		{
			if (process_token(e, iter, tok_len, pos))
				return (1);
			iter += tok_len;
			pos.x++;
		}
		free(line);
		pos.y++;
	}
	close(fd);
	return (0);
}

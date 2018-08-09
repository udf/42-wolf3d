/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 18:50:02 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/09 22:17:08 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	process_empty_token(t_cell *cell, char c)
{
	if (c != ' ')
		return ;
	cell->type = EMPTY;
}

static int	process_token(t_env *e, char *str, size_t len, t_ip2d pos)
{
	t_cell	cell;

	cell.type = UNKNOWN;
	if (str[0] == '_')
		process_empty_token(&cell, str[1]);
	if (str[0] == 'W')
		process_wall_token(&cell, str[1]);
	if (str[0] == 'D')
		process_door_token(&cell, str[1]);
	if (str[0] == 'K')
		process_key_token(&cell, str[1], pos);
	if (str[0] == '^')
		process_key_token(&cell, 0, pos);
	if (str[0] == 'P')
		process_prop_token(&cell, str[1]);
	if (str[0] == '@')
		process_player_token(&cell, str[1], e, pos);
	if (cell.type == UNKNOWN)
		return (SDL_SetError("%s\nUnknown token \"%.*s\" on line %zd;token %zd",
			SDL_GetError(), (int)len, str, pos.y + 1, pos.x + 1));
	vec_append(&e->world, &cell);
	return (0);
}

int			process_line(t_env *e, char *line, ssize_t line_n)
{
	size_t	tok_len;
	ssize_t	tok_n;

	tok_n = 0;
	while ((tok_len = seek_token(&line)) > 0)
	{
		if (process_token(e, line, tok_len, (t_ip2d){tok_n, line_n}))
			return (1);
		line += tok_len;
		tok_n++;
	}
	if (!e->world_w)
		e->world_w = tok_n;
	if (tok_n != e->world_w)
		return (SDL_SetError(
			"Incorrect number of tokens on line %zd (expected %zd)", tok_n,
			e->world_w));
	return (0);
}

int			load_map(t_env *e, const char *path)
{
	int		fd;
	char	*line;
	ssize_t	line_n;
	int		err;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (SDL_SetError("Could not open map file"));
	line_n = 0;
	while (get_next_line(fd, &line) == GNL_SUCCESS)
	{
		err = process_line(e, line, line_n);
		free(line);
		if (err)
			return (err);
		line_n++;
	}
	close(fd);
	e->world_h = line_n;
	return (0);
}

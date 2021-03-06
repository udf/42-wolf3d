/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:08:43 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/23 14:59:46 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static int		process_token(t_model_data *m, const char *str,
	size_t len, t_ip2d pos)
{
	int		error;
	t_cell	cell;

	error = !(str[0] == '_' && str[1] == ' ');
	cell.type = EMPTY;
	if (str[0] == 'W')
		error = process_wall_token(&cell, m->world.walls, str[1]);
	if (str[0] == 'D')
		error = process_door_token(&cell, &m->world.doors, str[1]);
	if (str[0] == 'K')
		error = process_key_token(&m->world.things, str[1], pos);
	if (str[0] == '^')
		error = process_key_token(&m->world.things, 0, pos);
	if (str[0] == 'P')
		error = process_prop_token(&m->world.things, str[1], pos);
	if (str[0] == '@')
		error = process_player_token(&m->me, str[1], pos);
	if (error)
	{
		return (SDL_SetError("%s\nUnknown token \"%.*s\" on line %zd:token %zd",
			SDL_GetError(), (int)len, str, pos.y + 1, pos.x + 1));
	}
	vec_append(&m->world.cells, &cell);
	return (0);
}

static size_t	seek_token(char **str)
{
	char	*iter;
	size_t	tok_len;

	iter = *str;
	while (iter && *iter && *iter == ' ')
		iter++;
	tok_len = 0;
	*str = iter;
	while (iter && iter[tok_len] && iter[tok_len] != ' ')
		tok_len++;
	return (tok_len);
}

static int		process_line(t_model_data *m, char *line, ssize_t line_n)
{
	size_t	tok_len;
	ssize_t	tok_n;

	tok_n = 0;
	while ((tok_len = seek_token(&line)) > 0)
	{
		if (process_token(m, line, tok_len, (t_ip2d){tok_n, line_n}))
			return (1);
		line += tok_len;
		tok_n++;
	}
	if (!m->world.w)
		m->world.w = tok_n;
	if (tok_n != m->world.w)
	{
		return (SDL_SetError("Line %zd: token miscount (expected %zd, got %zd)",
			line_n, m->world.w, tok_n));
	}
	return (0);
}

static void		fix_door_ptrs(t_model_data *m)
{
	size_t i;
	t_cell *cell;

	i = 0;
	while (i < m->world.cells.length)
	{
		cell = vec_get(&m->world.cells, i);
		if (cell->type == DOOR)
			cell->door = vec_get(&m->world.doors, (size_t)cell->door);
		i++;
	}
}

int				model_map_load(const char *map_path)
{
	int				fd;
	char			*line;
	ssize_t			line_n;
	int				err;
	t_model_data	*m;

	if ((fd = open(map_path, O_RDONLY)) < 0)
		return (SDL_SetError("Could not open map file"));
	m = model_get_real();
	line_n = 0;
	while (get_next_line(fd, &line) == GNL_SUCCESS)
	{
		err = process_line(m, line, line_n);
		free(line);
		if (err)
			return (err);
		line_n++;
	}
	close(fd);
	m->world.h = line_n;
	fix_door_ptrs(m);
	return (0);
}

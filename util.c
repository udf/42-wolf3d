/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 13:52:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/04 22:59:34 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

size_t	seek_token(char **str)
{
	char	*iter;
	size_t		tok_len;

	iter = *str;
	while (iter && *iter && *iter == ' ')
		iter++;
	tok_len = 0;
	*str = iter;
	while (iter && iter[tok_len] && iter[tok_len] != ' ')
		tok_len++;
	return (tok_len);
}

void	set_draw_colour(SDL_Renderer *ren, Uint32 col)
{
	SDL_SetRenderDrawColor(ren,
		(col >> 16) & 0xFF, (col >> 8) & 0xFF, col & 0xFF, 0xFF);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 23:50:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/16 23:33:59 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

static t_p2d	to_dir(float theta)
{
	t_p2d ret;

	theta = mod_deg(theta);
	ret.x = 0;
	ret.y = 0;
	if (theta > 0 && theta < 180)
		ret.y = 1;
	else if (theta > 180 && theta < 360)
		ret.y = -1;
	if ((theta > 0 && theta < 90) || (theta > 270 && theta < 360))
		ret.x = 1;
	else if (theta > 90 && theta < 270)
		ret.x = -1;
	return (ret);
}

static t_hit	hit_test(t_p2d dir, t_p2d pos, char is_vert)
{
	const t_cell	*cell;
	t_hit			hit;

	hit = (t_hit){NULL, {-1, -1}, fmodf(is_vert ? pos.y : pos.x, 1.0f), 0, 1};
	hit.pos = pos;
	pos.x -= (is_vert && dir.x < 0);
	pos.y -= (!is_vert && dir.y < 0);
	cell = model_get_cell(pos);
	if (cell && cell->type == WALL)
	{
		if (is_vert)
			hit.tex = (dir.x > 0 ? cell->wall->tex_w : cell->wall->tex_e);
		else
			hit.tex = (dir.y > 0 ? cell->wall->tex_n : cell->wall->tex_s);
	}
	else if (cell && cell->type == DOOR)
	{
		hit.tex = cell->door->tex;
		hit.v_shift = (float)cell->door->anim_state / 101.0f;
	}
	else if (cell)
		hit.valid = 0;
	return (hit);
}

static t_p2d	compute_step(float theta, t_p2d dir)
{
	const float	tan_theta = fabsf(tan_deg(theta));

	return (t_p2d){dir.x * (1 / tan_theta), dir.y * tan_theta};
}

static t_p2d	compute_inter(float theta, t_p2d dir, t_p2d *p, t_p2d p_delta)
{
	float	tmp;
	t_p2d	inter;

	tmp = 0;
	if (dir.x > 0)
		tmp = 1 - p_delta.x;
	else if (dir.x < 0)
		tmp = p_delta.x;
	inter.y = p->y + p_delta.y + tmp * fabsf(tan_deg(theta)) * dir.y;
	tmp = 0;
	if (dir.y > 0)
		tmp = 1 - p_delta.y;
	else if (dir.y < 0)
		tmp = p_delta.y;
	inter.x = p->x + p_delta.x + tmp / fabsf(tan_deg(theta)) * dir.x;
	p->x += (dir.x > 0);
	p->y += (dir.y > 0);
	return (inter);
}

t_hit			view_raycast(float theta, t_p2d p, t_p2d p_delta)
{
	const t_p2d	dir = to_dir(theta);
	const t_p2d	step = compute_step(theta, dir);
	t_p2d		inter;
	t_hit		hit;
	int safety = 0;

	SDL_SetError("params: %f, {%f, %f}, {%f, %f}\n",
		theta, p.x, p.y, p_delta.x, p_delta.y);
	inter = compute_inter(theta, dir, &p, p_delta);
	while (safety < 1000)
	{
		while (VAL_CAN_MOVE(inter.y, step.y, p.y) || VAL_CLOSE(inter.y, p.y))
		{
			if ((hit = hit_test(dir, (t_p2d){p.x, inter.y}, 1)).valid)
				return (hit);
			p.x += dir.x;
			inter.y += step.y;
		}
		while (VAL_CAN_MOVE(inter.x, step.x, p.x) || VAL_CLOSE(inter.x, p.x))
		{
			if ((hit = hit_test(dir, (t_p2d){inter.x, p.y}, 0)).valid)
				return (hit);
			p.y += dir.y;
			inter.x += step.x;
		}
		safety++;
	}
	// TODO: try to hit this
	printf("more than 1000 ray cast steps, wtf?\n");
	printf(SDL_GetError());
	exit(69);
	return (t_hit){NULL, {0, 0}, 0, 0, 0};
}

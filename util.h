/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 21:58:53 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/14 23:48:09 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <math.h>
# include <unistd.h>
# include "SDL.h"

typedef struct		s_p2d
{
	float			x;
	float			y;
}					t_p2d;

typedef struct		s_ip2d
{
	ssize_t			x;
	ssize_t			y;
}					t_ip2d;

float			mod_deg(float deg);
int				is_angle_between(float a, float start, float end); //TODO: check usage
void			post_exit_event(void);

float			sin_deg(float deg);
float			cos_deg(float deg);
float			tan_deg(float deg);
float			p2d_dist(t_p2d a, t_p2d b);
float			p2d_angle(t_p2d a, t_p2d b);

#endif

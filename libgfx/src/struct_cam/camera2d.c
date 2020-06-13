/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:32:09 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:11 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_cam2d		init_cam2d(void)
{
	t_cam2d		c;

	clean_cam2d(&c);
	c.fov = 3.1415927 / 3;
	c.half_fov = c.fov / 2.0f;
	c.speed_move = 100.;
	c.speed_angle = 100.;
	c.dir = 0;
	return (c);
}

void		clean_cam2d(t_cam2d *c)
{
	ft_bzero(c, sizeof(t_cam2d));
}

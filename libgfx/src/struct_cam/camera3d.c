/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:32:17 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:10 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_cam3d		init_cam3d(t_vecf3 from, t_vecf3 to, t_vecf3 tmp)
{
	t_cam3d	c;

	clean_cam3d(&c);
	matrice_cam3d(&c, from, to, tmp);
	return (c);
}

void		clean_cam3d(t_cam3d *c)
{
	ft_bzero(c, sizeof(t_cam3d));
}

void		matrice_cam3d(t_cam3d *c, t_vecf3 from, t_vecf3 to, t_vecf3 tmp)
{
	t_vecf3		forward;
	t_vecf3		right;
	t_vecf3		up;

	tmp.x = 0.0;
	tmp.y = 1.0;
	tmp.z = 0.0;
	forward = normalize(from - to);
	right = cross_product(normalize(tmp), forward);
	if (right.x == 0.0)
		right.x = 1.0;
	up = cross_product(forward, right);
	c->right = right;
	c->up = up;
	c->forward = forward;
	c->from = from;
	c->fov = M_PI / 3;
}

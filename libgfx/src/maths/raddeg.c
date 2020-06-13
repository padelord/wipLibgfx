/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raddeg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:15:48 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:13 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

float	deg2rad(float d)
{
	float	r;

	r = (d / 180.0f) * M_PI;
	return (r);
}

float	rad2deg(float r)
{
	float	d;

	d = (r / M_PI) * 180.0f;
	return (d);
}

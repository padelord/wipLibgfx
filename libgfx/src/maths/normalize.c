/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:13:04 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:15 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_point	normalize(t_point v)
{
	float	invlen;

	if ((v.x + v.y + v.z) != 0)
	{
		invlen = 1 / sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
		v.x *= invlen;
		v.y *= invlen;
		v.z *= invlen;
	}
	return (v);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_hsl_min_maj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:50:14 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:32 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

float			float_min(float *n)
{
	float	min;
	int		i;

	i = 0;
	min = n[i];
	while (i++ < 2)
	{
		if (min > n[i])
			min = n[i];
	}
	return (min);
}

float			float_max(float *n)
{
	float	max;
	int		i;

	i = 0;
	max = n[i];
	while (i++ < 2)
	{
		if (max < n[i])
			max = n[i];
	}
	return (max);
}

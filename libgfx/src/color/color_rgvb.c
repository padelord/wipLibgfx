/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgvb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:33:21 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:16 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_color	init_color(int color)
{
	t_color	c;
	int		mask;

	ft_bzero(&c, sizeof(t_color));
	mask = 0xFF;
	c.r = (color >> 16) & mask;
	c.g = (color >> 8) & mask;
	c.b = color & mask;
	c.color = color;
	return (c);
}

int		lerp_color(t_color s, t_color e, float t)
{
	int	r;
	int	g;
	int	b;

	if (s.color == e.color)
		return (s.color);
	r = (int)(s.r + (e.r - s.r) * t);
	g = (int)(s.g + (e.g - s.g) * t);
	b = (int)(s.b + (e.b - s.b) * t);
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

int		lerp_non_init_color(int a, int b, float t)
{
	return (lerp_color(init_color(a), init_color(b), t));
}

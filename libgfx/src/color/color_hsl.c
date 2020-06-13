/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_hsl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:50:14 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:26 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static t_vecf3	rgbtohsl2(float color[3], t_vecf3 hsl, float min, float max)
{
	if (max == color[0])
		hsl.z = ((color[1] - color[2]) / (max - min)) * 60.0f;
	else if (max == color[1])
		hsl.z = (2.0f + (color[2] - color[0]) / (max - min)) * 60.0f;
	else if (max == color[2])
		hsl.z = (4.0f + (color[0] - color[1]) / (max - min)) * 60.0f;
	if (hsl.z < 0)
		hsl.z += 360.0f;
	return (hsl);
}

t_vecf3			rgbtohsl(float r, float g, float b)
{
	float		color[3];
	t_vecf3		hsl;
	float		min;
	float		max;

	color[0] = r / 255.0f;
	color[1] = g / 255.0f;
	color[2] = b / 255.0f;
	min = float_min(color);
	max = float_max(color);
	hsl.x = (min + max) / 2.0f;
	if (min != max || (r != g && g != b && b != r))
	{
		if (hsl.x < 0.5f)
			hsl.y = (max - min) / (max + min);
		if (hsl.x > 0.5f)
			hsl.y = (max - min) / (2.0f - max - min);
	}
	else
		hsl.y = 0.0f;
	return (rgbtohsl2(color, hsl, min, max));
}

static float	check_value(float n)
{
	if (n > 1)
		n -= 1;
	if (n < 0)
		n += 1;
	return (n);
}

static float	generate_rgb(float color, t_vecf3 tmp)
{
	float ret;

	if (6.0f * color < 1.0f)
		ret = tmp.y + (tmp.x - tmp.y) * 6.0f * color;
	else if (2.0f * color < 1.0f)
		ret = tmp.x;
	else if (3.0f * color < 2.0f)
		ret = tmp.y + (tmp.x - tmp.y) * (0.666f - color) * 6.0f;
	else
		ret = tmp.y;
	return (ret);
}

int				hsltorgb(float hue, float sat, float lum)
{
	t_vecf3		tmp;
	int			red;
	int			green;
	int			blue;

	if (hue == 0 && sat == 0)
		return ((int)(lum * 255.0f) * 3);
	if (lum < 0.5f)
		tmp.x = lum * (1.0f + sat);
	else
		tmp.x = lum + sat - lum * sat;
	tmp.y = 2 * lum - tmp.x;
	tmp.z = hue / 360.0f;
	red = (int)((generate_rgb(check_value(tmp.z + 0.333), tmp) + 0.005f)
			* 255.0f);
	green = (int)((generate_rgb(check_value(tmp.z), tmp) + 0.005f) * 255.0f);
	blue = (int)((generate_rgb(check_value(tmp.z - 0.333), tmp) + 0.005f)
			* 255.0f);
	return (((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF));
}

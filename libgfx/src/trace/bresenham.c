/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:30:03 by crenaudi          #+#    #+#             */
/*   Updated: 2020/04/27 14:30:19 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void			init_anim_color(t_bresenham *b, int cwh[4], float scl_bert[2],
	t_vecf2 tr)
{
	b->c1 = b->tmp.x != 0.0 ? init_color(lerp_non_init_color(cwh[0], cwh[1],
		b->tmp.x)) : init_color(cwh[0]);
	b->c2 = b->tmp.y != 0.0 ? init_color(lerp_non_init_color(cwh[0], cwh[1],
		b->tmp.y)) : init_color(cwh[0]);
	b->t = vecf2_dist(b->p2 - b->p1);
	b->w = cwh[3];
	b->h = cwh[4];
	b->scl = scl_bert[0];
	b->bert = scl_bert[1];
	b->tr = tr;
}

t_bresenham		init_trace(t_point p[2], t_vecf3 z)
{
	t_bresenham b;

	ft_bzero(&b, sizeof(t_bresenham));
	b.tmp = z;
	b.p1 = (t_vecf2){(int)p[0].x, (int)p[0].y};
	b.p2 = (t_vecf2){(int)p[1].x, (int)p[1].y};
	b.dir.x = fabsf(b.p2.x - b.p1.x);
	b.dir.y = fabsf(b.p2.y - b.p1.y);
	b.sens.x = b.p1.x < b.p2.x ? 1 : -1;
	b.sens.y = b.p1.y < b.p2.y ? 1 : -1;
	return (b);
}

static void		putpx(t_img *img, t_vec2 i, t_vec2 size, int color)
{
	int	index;

	index = i.x + i.y * size.y;
	if (index < 0 || index >= size.x * size.y)
		return ;
	img->data[index] = color;
}

void			need_px(t_bresenham *b, t_img *img)
{
	int x;
	int y;

	x = b->p1.x + ((b->w / 2) + b->tr.y);
	y = b->p1.y + (((b->h / 2) - (int)b->scl) + b->tr.x);
	if ((x >= 0 && x <= b->w) && (y >= 0 && y <= (b->h)))
		putpx(img, (t_vec2){x, y}, (t_vec2){b->h, b->w}, lerp_color(b->c2,
			b->c1, fmod(((vecf2_dist(b->p2 - b->p1)) / b->t) + b->bert, 1.0)));
}

void			line(t_bresenham b, t_img *img)
{
	t_vec2	err;

	err.x = (b.dir.x > b.dir.y ? b.dir.x : -b.dir.y) / 2;
	err.y = 0;
	while ("OUIIIIIIIIIII")
	{
		need_px(&b, img);
		if (b.p1.x == b.p2.x && b.p1.y == b.p2.y)
			return ;
		err.y = err.x;
		if (err.y > -b.dir.x)
		{
			err.x -= b.dir.y;
			b.p1.x += b.sens.x;
		}
		if (err.y < b.dir.y)
		{
			err.x += b.dir.x;
			b.p1.y += b.sens.y;
		}
	}
}

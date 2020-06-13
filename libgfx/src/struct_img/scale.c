/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:31:18 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/02 04:18:42 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		set_scaledframe(t_u32 *src, t_vec2 ssize, t_u32 *dest,
		t_vec2 dsize)
{
	t_vec2		cd;
	t_vecf2		cs;
	t_vecf2		gap;

	gap = (t_vecf2){((float)ssize.x / (float)dsize.x),
			((float)ssize.y / (float)dsize.y)};
	cd.y = -1;
	cs.y = 0;
	while (++cd.y < dsize.y)
	{
		cd.x = -1;
		cs.x = 0;
		while (++cd.x < dsize.x)
		{
			dest[cd.x + cd.y * dsize.x] = src[((int)cs.x) + ((int)cs.y)
				* ssize.y];
			cs.x += gap.x;
		}
		cs.y += gap.y;
	}
}

t_texture	*tx_scaleto(t_texture *src, int x, int y)
{
	t_texture	*dest;
	int			i;

	if (!(dest = init_tx(0, (t_vec2){x, y}, src->nframes)))
		return (0);
	i = -1;
	while (++i < src->nframes)
		set_scaledframe(src->frames[i], src->size, dest->frames[i],
				(t_vec2){x, y});
	close_tx(&src);
	return (dest);
}

t_texture	*tx_scaleby(t_texture *src, float by)
{
	if (!src)
		return (0);
	return (tx_scaleto(src, (float)src->size.x * by,
						(float)src->size.y * by));
}

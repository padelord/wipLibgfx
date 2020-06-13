/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:30:35 by crenaudi          #+#    #+#             */
/*   Updated: 2020/04/25 04:13:55 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

int		apply_ext(t_u32 *src, t_vec2 size, t_img *img, t_vec2 pos)
{
	(void)src;
	if (pos.x > img->size.x || pos.y > img->size.y ||
		pos.x + size.x < 0 || pos.y + size.y < 0)
		return (0);
	return (1);
}

int		apply_tx(t_texture txt, t_img *img, t_vec2 pos, int frame)
{
	t_u32	*src;
	t_u32	*dest;
	t_vec2	i;

	if (pos.x > img->size.x || pos.y > img->size.y ||
		pos.x + txt.size.x < 0 || pos.y + txt.size.y < 0)
		return (apply_ext(txt.frames[frame], txt.size, img, pos));
	src = txt.frames[frame];
	dest = (t_u32*)img->data + pos.x + pos.y * img->size.x;
	i.y = -1;
	while (++i.y < txt.size.y)
	{
		i.x = -1;
		while (++i.x < txt.size.x)
		{
			if (!(*src == C_TRANSP))
				*dest = *src;
			++dest;
			++src;
		}
		dest += img->size.x - txt.size.x;
	}
	return (1);
}

int		apply_sprite(t_sprite *sprite, t_img *img)
{
	if (sprite->mod & SPRIT_ISANIM)
	{
		if (!(sprite->mod & SPRIT_ISINCD))
		{
			if (sprite->cframe == 0)
			{
				if (++sprite->tof > sprite->cd)
					sprite->mod |= SPRIT_ISINCD;
			}
			else if (++sprite->tof >= ANIM_SPEED)
			{
				sprite->cframe++;
				sprite->tof = 0;
			}
			if (sprite->cframe >= sprite->tx->nframes)
				sprite->cframe = 0;
		}
	}
	return (apply_tx(*(sprite->tx), img, sprite->pos, sprite->cframe));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padelord <padelord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 04:11:55 by padelord          #+#    #+#             */
/*   Updated: 2020/04/27 14:33:07 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void	close_tx(t_texture **p)
{
	t_texture	*t;

	if (!(*p))
		return ;
	t = *p;
	if (t->src)
	{
		ft_bzero(t->src, sizeof(int) * t->size.x * t->size.y * t->nframes);
		free(t->src);
	}
	if (t->frames)
	{
		ft_bzero(t->frames, sizeof(int*) * t->nframes);
		free(t->frames);
	}
	ft_bzero(t, sizeof(*t));
	free(t);
	p = 0;
}

void	close_sprite(t_sprite **sprite)
{
	if (!(*sprite))
		return ;
	close_tx(&((*sprite)->tx));
	ft_bzero(*sprite, sizeof(**sprite));
	free(*sprite);
	*sprite = 0;
}

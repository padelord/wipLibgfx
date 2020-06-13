/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:31:31 by crenaudi          #+#    #+#             */
/*   Updated: 2020/04/25 04:13:21 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

int		trigger_sprite(t_sprite *sprite)
{
	if (sprite->mod & SPRIT_ISANIM && sprite->mod & SPRIT_ISINCD)
	{
		sprite->mod ^= SPRIT_ISINCD;
		sprite->cframe++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_cal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:15:48 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:14 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_q		*quaternion_mult_real_num(t_q *q)
{
	float	r;

	r = 0.0;
	q->x = q->x * r;
	q->y = q->y * r;
	q->z = q->z * r;
	q->w = q->w * r;
	return (q);
}

t_q		*quaternion_add(t_q *q1, t_q *q2)
{
	t_q	*q;

	q = 0;
	q->x = q1->x + q2->x;
	q->y = q1->y + q2->y;
	q->z = q1->z + q2->z;
	q->w = q1->w + q2->w;
	return (q);
}

t_q		*quaternion_mult(t_q *q1, t_q *q2)
{
	t_q		*q;

	q = 0;
	if (q1 == NULL || q2 == NULL)
		return (NULL);
	q->x = (q1->x * q2->x) - (q1->y * q2->y)
		- (q1->z * q2->z) - (q1->w * q2->w);
	q->y = (q1->x * q2->y) + (q1->y * q2->x)
		+ (q1->z * q2->w) - (q1->w * q2->z);
	q->z = (q1->x * q2->z) - (q1->y * q2->w)
		+ (q1->z * q2->x) + (q1->w * q2->y);
	q->w = (q1->x * q2->w) + (q1->y * q2->z)
		- (q1->z * q2->y) + (q1->w * q2->x);
	return (q);
}

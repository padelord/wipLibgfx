/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:39:51 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 18:04:29 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_longmemcpy(long *dest, long *src, size_t n)
{
	while (n--)
		*dest++ = *src++;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src2;

	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	if (n >> 5)
	{
		ft_longmemcpy((long*)dest, (long*)src, n >> 3);
		dest2 += (n >> 3) << 3;
		src2 += (n >> 3) << 3;
		n &= 7U;
	}
	while (n-- > 0)
		*dest2++ = *src2++;
	return (dest);
}

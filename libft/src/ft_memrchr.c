/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:43:46 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 12:16:40 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*s2;
	unsigned char	c2;

	i = ft_strlen(s);
	s2 = (unsigned char *)s;
	c2 = (unsigned char)c;
	while (n--)
	{
		if (s2[i] == c2)
			return (s2 + i);
		i--;
	}
	return (NULL);
}

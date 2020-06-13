/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 16:44:32 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 12:19:26 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && len)
	{
		while ((len - j) != 0 && s1[i + j] == s2[j] && s1[i + j])
			j++;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
		j = 0;
		len--;
	}
	return (NULL);
}

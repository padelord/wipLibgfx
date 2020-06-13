/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:19:18 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 12:18:41 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;
	int		len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(copy = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strcpy(copy, s1);
	ft_strcat(copy, s2);
	copy[len] = '\0';
	return (copy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:08:47 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 12:16:09 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*pointeur;

	if (!(pointeur = (char *)malloc(sizeof(char) * (size))))
		return (NULL);
	ft_bzero(pointeur, size);
	return (pointeur);
}

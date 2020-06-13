/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:47:46 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 12:19:45 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int		count;
	int		is_c;

	is_c = 0;
	count = 0;
	while (*s != '\0')
	{
		if (is_c == 1 && *s == c)
			is_c = 0;
		if (is_c == 0 && *s != c)
		{
			is_c = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	ft_count_letter(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		s++;
		count++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nword;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	nword = ft_count_word((const char *)s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) *
					(ft_count_word((char *)s, c) + 1))))
		return (NULL);
	while (nword--)
	{
		while (*s == c && *s != '\0')
			s++;
		tab[i] = ft_strsub((const char *)s, 0,
				ft_count_letter((const char *)s, c));
		if (tab[i] == NULL)
			return (NULL);
		s = s + ft_count_letter(s, c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

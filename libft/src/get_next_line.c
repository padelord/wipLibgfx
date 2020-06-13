/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:58:03 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 12:20:23 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		need_to_stock(char **rest, char **line, int *i, int *ret)
{
	char	*tmp;

	if (!ft_strchr(*rest, '\n') || *ret == 0)
	{
		*line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	else
	{
		*line = ft_strsub(*rest, 0, *i);
		*i += 1;
		tmp = *rest;
		*rest = ft_strsub(*rest, *i, ft_strlen(*rest) - *i);
		free(tmp);
		tmp = NULL;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*rest = NULL;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp;
	int				i;

	i = 0;
	ret = 1;
	while (rest == NULL || (!ft_strchr(rest, '\n') && ret > 0))
	{
		if (fd < 0 || (ret = read(fd, buf, BUFF_SIZE)) < 0 || line == NULL)
			return (-1);
		buf[ret] = '\0';
		tmp = rest;
		rest = (rest == NULL) ? ft_strdup(buf) : ft_strjoin(rest, buf);
		free(tmp);
		tmp = NULL;
	}
	if (ret == 0 && rest[i] == '\0')
		return (0);
	while (rest[i] != '\n' && rest[i] != '\0')
		i++;
	return (need_to_stock(&rest, line, &i, &ret));
}

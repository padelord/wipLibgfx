/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:15:42 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/14 12:17:31 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long nb)
{
	int	i;

	i = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		i = i * 10;
	}
	return (i);
}

void		ft_putnbr_fd(int n, int fd)
{
	long	nb;
	long	modulo;
	int		i;

	nb = n;
	while (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	i = ft_count(nb);
	while (i > 0)
	{
		modulo = nb % i;
		nb = nb / i;
		ft_putchar_fd(nb + 48, fd);
		i = i / 10;
		nb = modulo;
	}
}

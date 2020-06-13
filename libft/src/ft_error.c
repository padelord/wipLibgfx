/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padelord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:33:47 by padelord          #+#    #+#             */
/*   Updated: 2020/04/24 18:34:33 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_error(int set, unsigned int v)
{
	static unsigned int	err = 0;

	if (set)
		err = v;
	return (err);
}

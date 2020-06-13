/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:30:53 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/12 19:42:09 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_img	*init_image(void *mlx_ptr, int w, int h)
{
	t_img	*img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	ft_bzero(img, sizeof(t_img));
	img->ptr = mlx_new_image(mlx_ptr, w, h);
	img->data = (t_u32 *)(mlx_get_data_addr(img->ptr, &img->bpp, &img->sl,
		&img->endian));
	img->size = (t_vec2){w, h};
	return (img);
}

void	clean_image(t_img *img, int width, int height)
{
	ft_bzero(img->data, width * height * (img->bpp / 8));
}

void	close_image(t_img *img, void *mlx_ptr, int width, int height)
{
	if (img != NULL)
	{
		clean_image(img, width, height);
		mlx_destroy_image(mlx_ptr, img->ptr);
		free(img);
	}
}

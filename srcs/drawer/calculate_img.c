/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:33:33 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/26 13:26:02 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_img(t_scene *scene)
{
	int			x;
	int			y;
	t_transform	transform;
	t_pixel		pixel;
	uint32_t	color;

	transform = init_transform(scene);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel.r_vec = get_pixel_vector(scene, &transform, x, y);
			hit_objects(scene, &pixel);
			color = get_color(scene, &pixel);
			mlx_put_pixel(scene->img, x, y, color);
		}
	}
}

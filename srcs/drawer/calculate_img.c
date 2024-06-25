/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:33:33 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/25 17:29:06 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	color_to_hex(t_color color);

void	calculate_img(t_scene *scene)
{
	int			x;
	int			y;
	t_transform	transform;
	t_pixel		pixel;
	t_color		color;

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
			mlx_put_pixel(scene->img, x, y, color_to_hex(color));
		}
	}
}

uint32_t	color_to_hex(t_color color)
{
	uint32_t	res;

	res = color.r;
	res = (res << 8) + color.g;
	res = (res << 8) + color.b;
	return (res << 8 | 0xFF);
}

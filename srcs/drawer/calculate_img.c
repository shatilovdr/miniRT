/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:33:33 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/28 11:29:12 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_img(t_scene *scene)
{
	int			x;
	int			y;
	t_transform	transform;
	t_ray		ray;
	uint32_t	color;

	transform = init_transform(scene);
	ray.origin = scene->cam->pos;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray.direction = get_ray_direction(scene, &transform, x, y);
			hit_objects(scene, &ray);
			color = get_color(scene, &ray);
			mlx_put_pixel(scene->img, x, y, color);
		}
	}
}

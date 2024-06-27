/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/28 11:27:56 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	vec3_rotate(t_vec3 vec, t_vec3 *axis, float sin, float cos);

t_vec3	get_ray_direction(t_scene *scene, t_transform *t, int x, int y)
{
	t_vec3	r_vec;

	r_vec.z = t->z_dist;
	r_vec.x = x - WIDTH / 2;
	r_vec.y = HEIGHT / 2 - y;
	if (scene->cam->orientation.z < 0)
		r_vec.y *= -1;
	r_vec = vec3_rotate(r_vec, &t->yaw_axis, t->yaw_sin, t->yaw_cos);
	r_vec = vec3_rotate(r_vec, &t->pitch_axis, t->pitch_sin, t->pitch_cos);
	r_vec = vec3_unit(r_vec);
	return (r_vec);
}

static t_vec3	vec3_rotate(t_vec3 vec, t_vec3 *axis, float sin, float cos)
{
	t_vec3	res;

	res.x = (cos + (1 - cos) * axis->x * axis->x) * vec.x
		+ ((1 - cos) * axis->x * axis->y - sin * axis->z) * vec.y
		+ ((1 - cos) * axis->x * axis->z + sin * axis->y) * vec.z;
	res.y
		= ((1 - cos) * axis->x * axis->y + sin * axis->z) * vec.x
		+ (cos + (1 - cos) * axis->y * axis->y) * vec.y
		+ ((1 - cos) * axis->y * axis->z - sin * axis->x) * vec.z;
	res.z
		= ((1 - cos) * axis->x * axis->z - sin * axis->y) * vec.x
		+ ((1 - cos) * axis->y * axis->z + sin * axis->x) * vec.y
		+ (cos + (1 - cos) * axis->z * axis->z) * vec.z;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/29 14:54:49 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_ray_direction(t_transform *t, int x, int y)
{
	t_vec3	r_vec;
	t_vec3	pixel_pos;

	pixel_pos.x = (x - WIDTH / 2.0f);
	pixel_pos.y = (HEIGHT / 2.0f - y);
	pixel_pos.z = t->z_dist;
	r_vec.x = t->cam_right.x * pixel_pos.x + t->cam_up.x * pixel_pos.y
		+ t->cam_forward.x * pixel_pos.z;
	r_vec.y = t->cam_right.y * pixel_pos.x + t->cam_up.y * pixel_pos.y
		+ t->cam_forward.y * pixel_pos.z;
	r_vec.z = t->cam_right.z * pixel_pos.x + t->cam_up.z * pixel_pos.y
		+ t->cam_forward.z * pixel_pos.z;
	return (vec3_unit(r_vec));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:12:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/25 11:39:42 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_transform	init_transform(t_scene *scene)
{
	t_transform		transform;
	const t_camera	*camera;
	t_vec3			orientation;

	camera = scene->cam;
	orientation = camera->orientation;
	orientation.y = 0;
	orientation = vec3_unit(orientation);
	transform.yaw_axis = cross(((t_vec3){0, 0, 1}), orientation);
	transform.yaw_cos = dot((t_vec3){0, 0, 1}, orientation);
	transform.yaw_sin = sin(acos(transform.yaw_cos));
	transform.pitch_axis = cross(orientation, (t_vec3){0, 1, 0});
	transform.pitch_sin = camera->orientation.y;
	transform.pitch_cos = cos(asin(transform.pitch_sin));
	transform.z_dist = (WIDTH / 2) / tan((camera->fov / 2) / 180 * M_PI);
	return (transform);
}


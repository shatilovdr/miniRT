/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:12:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/09 11:59:30 by dshatilo         ###   ########.fr       */
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
	transform.yaw_axis = vec3_cross(((t_vec3){0, 0, 1}), orientation);
	transform.yaw_cos = vec3_dot((t_vec3){0, 0, 1}, orientation);
	transform.yaw_sin = sin(acos(transform.yaw_cos));
	transform.pitch_axis = vec3_cross(orientation, (t_vec3){0, 1, 0});
	transform.pitch_sin = camera->orientation.y;
	transform.pitch_cos = cos(asin(transform.pitch_sin));
	transform.z_dist = (WIDTH / 2) / tan((camera->fov / 2.0f) / 180 * M_PI);
	return (transform);
}
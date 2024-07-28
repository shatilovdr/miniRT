/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:12:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/29 14:59:46 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_transform	init_transform(t_scene *scene)
{
	t_transform		transform;
	t_vec3			forward;
	const t_vec3	world_up = {0, 1, 0};

	forward = vec3_unit(scene->cam->orientation);
	transform.cam_forward = forward;
	if (fabsf(vec3_dot(forward, world_up)) > 0.9999)
	{
		transform.cam_right = vec3_cross(forward, (t_vec3){0, 0, 1});
	}
	else
	{
		transform.cam_right = vec3_cross(world_up, forward);
	}
	transform.cam_up = vec3_cross(forward, transform.cam_right);
	transform.z_dist = (WIDTH / 2)
		/ tanf((scene->cam->fov / 2.0f) / 180 * M_PI);
	return (transform);
}

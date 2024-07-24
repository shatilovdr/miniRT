/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:13:45 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/23 14:24:49 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_objects(t_scene *scene, t_ray *ray)
{
	ray->hp.type = OBJ_NONE;
	hit_spheres(scene->spheres, ray);
	hit_planes(scene->planes, ray);
	hit_cylinders(scene->cylinders, ray);
	hit_cones(scene->cones, ray);
}

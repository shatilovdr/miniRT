/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:13:45 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/10 23:26:09 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_objects(t_scene *scene, t_ray *ray)
{
	ray->type = OBJ_NONE;
	hit_spheres(scene->spheres, ray);
	hit_planes(scene->planes, ray);
}

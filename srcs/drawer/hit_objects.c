/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:13:45 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/27 22:43:41 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_objects(t_scene *scene, t_ray *ray)
{
	ray->type = OBJ_NONE;
	hit_spheres(scene->spheres, ray);
}

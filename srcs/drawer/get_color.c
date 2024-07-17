/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:03:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/17 16:48:04 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_color_sphere(t_ray *ray);
t_color	get_color_plane(t_ray *ray);

uint32_t	get_color(t_scene *scene, t_ray *ray)
{
	t_color	color;

	if (ray->hp.type == OBJ_NONE)
		return (0xFF);
	else if (ray->hp.type == OBJ_SPH)
		color = get_color_sphere(ray);
	else if (ray->hp.type == OBJ_PLN)
		color = get_color_plane(ray);
	else
		color = (t_color){0};
	color = add_lights(ray, scene, color);
	return (color_to_int(color));
}

t_color	get_color_sphere(t_ray *ray)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ray->hp.obj;
	return (sphere->color);
}

t_color	get_color_plane(t_ray *ray)
{
	t_plane	*plane;

	plane = (t_plane *)ray->hp.obj;
	return (plane->color);
}

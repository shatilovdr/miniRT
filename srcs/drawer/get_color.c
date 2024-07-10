/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:03:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/10 21:26:37 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color			get_color_sphere(t_ray *ray);

uint32_t	get_color(t_scene *scene, t_ray *ray)
{
	t_color	color;

	if (ray->type == OBJ_NONE)
		return (0xFF);
	if (ray->type == OBJ_SPH)
		color = get_color_sphere(ray);
	else
		color = (t_color){0};
	color = add_lights(ray, scene, color);
	return (color_to_int(color));
}

t_color	get_color_sphere(t_ray *ray)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ray->obj;
	return (sphere->color);
}

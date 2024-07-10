/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_planes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/10 23:25:12 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_plane(t_plane *plane, t_ray *ray);

void	hit_planes(const t_list *planes, t_ray *ray)
{
	t_plane	*plane;
	t_ray	temp;

	temp = *ray;
	while (planes)
	{
		plane = (t_plane *)planes->blk;
		if (hit_plane(plane, &temp) == true
			&& (temp.dist < ray->dist || ray->type == OBJ_NONE))
		{
			ray->type = OBJ_PLN;
			ray->obj = temp.obj;
			ray->dist = temp.dist;
			ray->h_point = temp.h_point;
			ray->hp_norm = temp.hp_norm;
		}
		planes = planes->next;
	}
}

static bool	hit_plane(t_plane *plane, t_ray *ray)
{
	t_vec3	normal;

	normal = plane->normal;
	if (vec3_dot(normal, ray->direction) == 0
		|| vec3_dot(vec3_unit(vec3_sub(plane->pos, ray->origin)),
			normal) == 0)
		return (false);
	if (vec3_dot(ray->direction, normal) > 0)
		normal = vec3_scale(normal, -1);
	ray->dist = vec3_dot(vec3_sub(plane->pos, ray->origin), normal)
		/ vec3_dot(ray->direction, normal);
	if (ray->dist <= 0)
		return (false);
	ray->h_point = vec3_add(ray->origin, vec3_scale(ray->direction, ray->dist));
	ray->hp_norm = normal;
	ray->obj = plane;
	return (true);
}

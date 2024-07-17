/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_planes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/17 16:58:46 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_plane(t_plane *plane, t_ray *ray, t_hp *hp);

void	hit_planes(const t_list *planes, t_ray *ray)
{
	t_plane	*plane;
	t_hp	hp;

	while (planes)
	{
		plane = (t_plane *)planes->blk;
		if (hit_plane(plane, ray, &hp) == true
			&& (hp.dist < ray->hp.dist || ray->hp.type == OBJ_NONE))
			ray->hp = hp;
		planes = planes->next;
	}
}

static bool	hit_plane(t_plane *plane, t_ray *ray, t_hp *hp)
{
	t_vec3	normal;

	normal = plane->normal;
	if (vec3_dot(normal, ray->direction) == 0
		|| vec3_dot(vec3_unit(vec3_sub(plane->pos, ray->origin)),
			normal) == 0)
		return (false);
	if (vec3_dot(ray->direction, normal) > 0)
		normal = vec3_scale(normal, -1);
	hp->dist = vec3_dot(vec3_sub(plane->pos, ray->origin), normal)
		/ vec3_dot(ray->direction, normal);
	if (hp->dist <= 0)
		return (false);
	hp->type = OBJ_PLN;
	hp->obj = plane;
	hp->loc = vec3_add(ray->origin, vec3_scale(ray->direction, hp->dist));
	hp->norm = normal;
	return (true);
}

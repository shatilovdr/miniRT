/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_conics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:44:38 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/20 10:04:01 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_base(t_conic *c, t_ray *ray, t_hp *hp, t_vec3 shift)
{
	const t_plane	plane = {vec3_add(c->pos, shift), c->axis,
		0, 0, (t_color){0}, 0, NULL};

	if (hit_plane(&plane, ray, hp) == true
		&& vec3_distance(hp->pos, plane.pos) <= c->diameter / 2)
	{
		hp->type = OBJ_CONIC;
		hp->surf_type = BASE;
	}
	else
		hp->type = OBJ_NONE;
}

t_hp	*select_closest_hp(t_hp *a, t_hp *b)
{
	if (a->type == OBJ_NONE)
		return (b);
	if (b->type == OBJ_NONE)
		return (a);
	if (a->dist < b->dist)
		return (a);
	else
		return (b);
}

void	check_conic_intersection(
		t_conic *conic, t_ray *ray, t_quad_eq *eq, t_hp *hp)
{
	float	height;
	t_hp	hp1;
	t_hp	hp2;

	hp1.type = OBJ_NONE;
	hp2.type = OBJ_NONE;
	hp1.dist = -eq->b - sqrt(eq->discriminant);
	hp2.dist = -eq->b + sqrt(eq->discriminant);
	if (hp1.dist >= EPSILON)
	{
		hp1.pos = vec3_add(ray->origin, vec3_scale(ray->direction, hp1.dist));
		height = vec3_dot(vec3_sub(hp1.pos, conic->pos), conic->axis);
		if (height > -0.001f && height <= conic->height)
			hp1.type = OBJ_CONIC;
	}
	if (hp2.dist >= EPSILON)
	{
		hp2.pos = vec3_add(ray->origin, vec3_scale(ray->direction, hp2.dist));
		height = vec3_dot(vec3_sub(hp2.pos, conic->pos), conic->axis);
		if (height > -0.001f && height <= conic->height)
			hp2.type = OBJ_CONIC;
	}
	*hp = *select_closest_hp(&hp1, &hp2);
}

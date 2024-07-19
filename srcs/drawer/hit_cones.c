/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:25:08 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/19 18:08:23 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_cone(t_cone *cone, t_ray *ray, t_hp *hp);
static void	hit_cone_base(
				t_cone *cone, t_ray *ray, t_hp *hp, t_vec3 shift);
static void	hit_curved_surface_cone(t_cone *cone, t_ray *ray, t_hp *hp);
static void	check_cone_intersection(
				t_cone *cone, t_ray *ray, t_quad_eq *eq, t_hp *hp);

void	hit_cones(const t_list *cones, t_ray *ray)
{
	t_cone	*cone;
	t_hp	hp;

	while (cones)
	{
		cone = (t_cone *)cones->blk;
		if (hit_cone(cone, ray, &hp) == true
			&& (hp.dist < ray->hp.dist || ray->hp.type == OBJ_NONE))
			ray->hp = hp;
		cones = cones->next;
	}
}

static bool	hit_cone(t_cone *cone, t_ray *ray, t_hp *hp)
{
	t_hp	base;
	t_hp	curved_surface;
	t_hp	*temp;

	hit_cone_base(cone, ray, &base,
		vec3_scale(cone->axis, cone->height));
	hit_curved_surface_cone(cone, ray, &curved_surface);
	temp = select_closest_hp(&base, &curved_surface);
	if (temp->type == OBJ_NONE)
		return (false);
	temp->obj = cone;
	*hp = *temp;
	return (true);
}

static void	hit_cone_base(
			t_cone *co, t_ray *ray, t_hp *hp, t_vec3 shift)
{
	const t_plane	plane = {vec3_add(co->pos, shift), co->axis, (t_color){0}};

	if (hit_plane(&plane, ray, hp) == true
		&& vec3_distance(hp->pos, plane.pos) <= co->diameter / 2)
	{
		hp->type = OBJ_CONE;
		hp->surf_type = BASE;
	}
	else
		hp->type = OBJ_NONE;
}

static void	hit_curved_surface_cone(t_cone *cone, t_ray *ray, t_hp *hp)
{
	t_quad_eq	eq;
	t_vec3		vec;
	float		angle;
	t_vec3		hp_to_con_pos;
	t_vec3		proj;
	t_vec3		norm;

	hp->type = OBJ_NONE;
	angle = atan((cone->diameter / 2) / cone->height);
	vec = vec3_sub(ray->origin, cone->pos);
	eq.a = 1 - (1 + pow(tan(angle), 2))
		* pow(vec3_dot(ray->direction, cone->axis), 2);
	eq.b = (vec3_dot(ray->direction, vec) - vec3_dot(ray->direction, cone->axis)
			* (1 + pow(tan(angle), 2)) * vec3_dot(vec, cone->axis)) / eq.a;
	eq.c = vec3_dot(vec, vec) - (1 + pow(tan(angle), 2))
		* pow(vec3_dot(vec, cone->axis), 2);
	eq.discriminant = eq.b * eq.b - eq.c / eq.a;
	if (eq.discriminant < 0)
		return ;
	check_cone_intersection(cone, ray, &eq, hp);
	if (hp->type == OBJ_NONE)
		return ;
	hp->surf_type = CURVED;
	hp_to_con_pos = vec3_sub(hp->pos, cone->pos);
	proj = vec3_scale(cone->axis, vec3_dot(hp_to_con_pos, cone->axis)
			/ vec3_dot(cone->axis, cone->axis));
	norm = vec3_unit(vec3_sub(hp_to_con_pos, proj));
	hp->norm
		= vec3_unit(vec3_sub(norm, vec3_scale(cone->axis, tan(angle))));
	if (vec3_dot(ray->direction, hp->norm) > 0)
		hp->norm = vec3_scale(hp->norm, -1);
}

static void	check_cone_intersection(
		t_cone *cone, t_ray *ray, t_quad_eq *eq, t_hp *hp)
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
		height = vec3_dot(vec3_sub(hp1.pos, cone->pos), cone->axis);
		if (height > -0.001f && height <= cone->height)
			hp1.type = OBJ_CONE;
	}
	if (hp2.dist >= EPSILON)
	{
		hp2.pos = vec3_add(ray->origin, vec3_scale(ray->direction, hp2.dist));
		height = vec3_dot(vec3_sub(hp2.pos, cone->pos), cone->axis);
		if (height > -0.001f && height <= cone->height)
			hp2.type = OBJ_CONE;
	}
	*hp = *select_closest_hp(&hp1, &hp2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:25:08 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/19 18:57:15 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_cone(t_conic *cone, t_ray *ray, t_hp *hp);
static void	hit_curved_surface_cone(t_conic *cone, t_ray *ray, t_hp *hp);
static void	solve_quad_eq_cone(
				t_quad_eq *eq, float angle, t_conic *cone, t_ray *ray);

void	hit_cones(const t_list *cones, t_ray *ray)
{
	t_conic	*cone;
	t_hp	hp;

	while (cones)
	{
		cone = (t_conic *)cones->blk;
		if (hit_cone(cone, ray, &hp) == true
			&& (hp.dist < ray->hp.dist || ray->hp.type == OBJ_NONE))
			ray->hp = hp;
		cones = cones->next;
	}
}

static bool	hit_cone(t_conic *cone, t_ray *ray, t_hp *hp)
{
	t_hp	base;
	t_hp	curved_surface;
	t_hp	*temp;

	hit_base(cone, ray, &base,
		vec3_scale(cone->axis, cone->height));
	hit_curved_surface_cone(cone, ray, &curved_surface);
	temp = select_closest_hp(&base, &curved_surface);
	if (temp->type == OBJ_NONE)
		return (false);
	temp->obj = cone;
	*hp = *temp;
	return (true);
}

static void	hit_curved_surface_cone(t_conic *cone, t_ray *ray, t_hp *hp)
{
	t_quad_eq	eq;
	float		angle;
	t_vec3		hp_to_con_pos;
	t_vec3		proj;
	t_vec3		norm;

	hp->type = OBJ_NONE;
	angle = atan((cone->diameter / 2) / cone->height);
	solve_quad_eq_cone(&eq, angle, cone, ray);
	if (eq.discriminant < 0)
		return ;
	check_conic_intersection(cone, ray, &eq, hp);
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

static void	solve_quad_eq_cone(
			t_quad_eq *eq, float angle, t_conic *cone, t_ray *ray)
{
	t_vec3		vec;

	vec = vec3_sub(ray->origin, cone->pos);
	eq->a = 1 - (1 + pow(tan(angle), 2))
		* pow(vec3_dot(ray->direction, cone->axis), 2);
	eq->b = (vec3_dot(ray->direction, vec)
			- vec3_dot(ray->direction, cone->axis) * (1 + pow(tan(angle), 2))
			* vec3_dot(vec, cone->axis)) / eq->a;
	eq->c = vec3_dot(vec, vec) - (1 + pow(tan(angle), 2))
		* pow(vec3_dot(vec, cone->axis), 2);
	eq->discriminant = eq->b * eq->b - eq->c / eq->a;
}

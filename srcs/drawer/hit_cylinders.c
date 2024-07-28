/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/29 15:02:35 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_cylinder(t_conic *cylinder, t_ray *ray, t_hp *hp);
static void	hit_curved_surface(t_conic *cylinder, t_ray *ray, t_hp *hp);
static void	solve_quad_eq_cylinder(
				t_quad_eq *eq, t_conic *cylinder, t_ray *ray);

void	hit_cylinders(const t_list *cylinders, t_ray *ray)
{
	t_conic	*cylinder;
	t_hp	hp;

	while (cylinders)
	{
		cylinder = (t_conic *)cylinders->blk;
		if (hit_cylinder(cylinder, ray, &hp) == true
			&& (hp.dist < ray->hp.dist || ray->hp.type == OBJ_NONE))
			ray->hp = hp;
		cylinders = cylinders->next;
	}
}

static bool	hit_cylinder(t_conic *cylinder, t_ray *ray, t_hp *hp)
{
	t_hp	base_1;
	t_hp	base_2;
	t_hp	curved_surface;
	t_hp	*temp;

	hit_base(cylinder, ray, &base_1, (t_vec3){0});
	hit_base(cylinder, ray, &base_2,
		vec3_scale(cylinder->axis, cylinder->height));
	hit_curved_surface(cylinder, ray, &curved_surface);
	temp = select_closest_hp(&base_1, &base_2);
	temp = select_closest_hp(temp, &curved_surface);
	if (temp->type == OBJ_NONE)
		return (false);
	temp->obj = cylinder;
	*hp = *temp;
	return (true);
}

static void	hit_curved_surface(t_conic *cylinder, t_ray *ray, t_hp *hp)
{
	t_quad_eq	eq;
	t_vec3		hp_to_cyl_pos;
	t_vec3		proj;

	hp->type = OBJ_NONE;
	solve_quad_eq_cylinder(&eq, cylinder, ray);
	if (eq.discriminant < 0)
		return ;
	check_conic_intersection(cylinder, ray, &eq, hp);
	if (hp->type == OBJ_NONE)
		return ;
	hp->surf_type = CURVED;
	hp_to_cyl_pos = vec3_sub(hp->pos, cylinder->pos);
	proj = vec3_scale(cylinder->axis, vec3_dot(hp_to_cyl_pos, cylinder->axis)
			/ vec3_dot(cylinder->axis, cylinder->axis));
	hp->norm = vec3_unit(vec3_sub(hp_to_cyl_pos, proj));
	if (vec3_dot(ray->direction, hp->norm) > 0)
		hp->norm = vec3_scale(hp->norm, -1);
}

static void	solve_quad_eq_cylinder(
			t_quad_eq *eq, t_conic *cylinder, t_ray *ray)
{
	t_vec3		vec;

	vec = vec3_sub(ray->origin, cylinder->pos);
	eq->a = vec3_dot2(vec3_cross(ray->direction, cylinder->axis));
	eq->b = (vec3_dot(vec, ray->direction) - vec3_dot(cylinder->axis, vec)
			* vec3_dot(cylinder->axis, ray->direction)) / eq->a;
	eq->c = vec3_dot2(vec) - powf(vec3_dot(cylinder->axis, vec), 2)
		- powf(cylinder->diameter / 2, 2);
	eq->discriminant = eq->b * eq->b - eq->c / eq->a;
}

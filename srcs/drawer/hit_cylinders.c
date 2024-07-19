/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/19 10:26:41 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hp *hp);
static void	hit_cylinder_base(
				t_cylinder *cy, t_ray *ray, t_hp *hp, t_vec3 shift);
static bool	hit_curved_surface(t_cylinder *cylinder, t_ray *ray, t_hp *hp);
static t_hp	*select_closest_hp(t_hp *a, t_hp *b);

void	hit_cylinders(const t_list *cylinders, t_ray *ray)
{
	t_cylinder	*cylinder;
	t_hp		hp;

	while (cylinders)
	{
		cylinder = (t_cylinder *)cylinders->blk;
		if (hit_cylinder(cylinder, ray, &hp) == true
			&& (hp.dist < ray->hp.dist || ray->hp.type == OBJ_NONE))
			ray->hp = hp;
		cylinders = cylinders->next;
	}
}

static bool	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hp *hp)
{
	t_hp	base_1;
	t_hp	base_2;
	t_hp	curved_surface;
	t_hp	*temp;

	base_1.surf_type = CY_BASE_1;
	base_2.surf_type = CY_BASE_1;
	curved_surface.surf_type = CY_CURVED;
	base_1.type = OBJ_NONE;
	base_2.type = OBJ_NONE;
	curved_surface.type = OBJ_NONE;
	hit_cylinder_base(cylinder, ray, &base_1, (t_vec3){0});
	hit_cylinder_base(cylinder, ray, &base_2,
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

static void	hit_cylinder_base(
			t_cylinder *cy, t_ray *ray, t_hp *hp, t_vec3 shift)
{
	const t_plane	plane = {vec3_add(cy->pos, shift), cy->axis, (t_color){0}};

	if (hit_plane(&plane, ray, hp) == true
		&& vec3_distance(hp->loc, plane.pos) <= cy->diameter / 2)
		hp->type = OBJ_CYL;
	else
		hp->type = OBJ_NONE;
}

static t_hp	*select_closest_hp(t_hp *a, t_hp *b)
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

// static bool	hit_curved_surface(t_cylinder *cylinder, t_ray *ray, t_hp *hp)
// {
// 	float			a;
// 	float			b;
// 	float			c;
// 	float			discriminant;
// 	const t_vec3	vec = vec3_sub(ray->origin, cylinder->pos);

// 	a = vec3_dot2(vec3_cross(ray->direction, cylinder->axis));
// 	b = 2 * (vec3_dot(vec, ray->direction) - vec3_dot(cylinder->axis, vec)
// 			* vec3_dot(cylinder->axis, ray->direction));
// 	c = vec3_dot2(vec) - pow(vec3_dot(cylinder->axis, vec), 2)
// 		- pow(cylinder->diameter / 2, 2);
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (false);
// 	hp->dist = (-b - sqrt(discriminant)) / (2 * a);
// 	if (hp->dist <= EPSILON)
// 		hp->dist = (-b + sqrt(discriminant)) / (2 * a);
// 	if (hp->dist <= EPSILON)
// 		return (false);
// 	hp->type = OBJ_CYL;
// 	hp->loc = vec3_add(ray->origin, vec3_scale(ray->direction, hp->dist));
// 	hp->norm = vec3_unit(vec3_sub(hp->loc, cylinder->pos));
// 	if (vec3_dot(ray->direction, hp->norm) > 0)
// 		hp->norm = vec3_scale(hp->norm, -1);
// 	return (true);
// }

static void	hit_curved_surface(t_cylinder *cylinder, t_ray *ray, t_hp *hp)
{
	t_quadratic_equation	eq;
	t_hp					hp1;
	t_hp					hp2;
	const t_vec3			vec = vec3_sub(ray->origin, cylinder->pos);

	eq.a = vec3_dot2(vec3_cross(ray->direction, cylinder->axis));
	eq.b = (vec3_dot(vec, ray->direction) - vec3_dot(cylinder->axis, vec)
			* vec3_dot(cylinder->axis, ray->direction)) / eq.a;
	eq.c = vec3_dot2(vec) - pow(vec3_dot(cylinder->axis, vec), 2)
		- pow(cylinder->diameter / 2, 2);
	eq.discriminant = eq.b * eq.b - eq.c / eq.a;
	hp1.dist = -eq.b - sqrt(eq.discriminant);
	hp2.dist = -eq.b + sqrt(eq.discriminant);
	function(cylinder, ray, &hp1);
	function(cylinder, ray, &hp2);
	*hp = *select_closest_hp(&hp1, &hp2);
}

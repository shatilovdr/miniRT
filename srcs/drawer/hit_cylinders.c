/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/18 09:20:58 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hp *hp);
static void	hit_cylinder_base(
				t_cylinder *cy, t_ray *ray, t_hp *hp, t_vec3 shift);
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

	if (hit_plane(&plane, ray, &hp) == true
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
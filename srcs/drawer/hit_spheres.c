/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/18 18:24:19 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hp *hp);

void	hit_spheres(const t_list *spheres, t_ray *ray)
{
	t_sphere	*sphere;
	t_hp		hp;

	while (spheres)
	{
		sphere = (t_sphere *)spheres->blk;
		if (hit_sphere(sphere, ray, &hp) == true
			&& (hp.dist < ray->hp.dist || ray->hp.type == OBJ_NONE))
			ray->hp = hp;
		spheres = spheres->next;
	}
}

static bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hp *hp)
{
	t_quadratic_equation	eq;
	t_vec3					sp_vec;

	sp_vec = vec3_sub(ray->origin, sphere->pos);
	eq.a = vec3_dot(ray->direction, ray->direction);
	eq.b = vec3_dot(sp_vec, ray->direction) / eq.a;
	eq.c = vec3_dot(sp_vec, sp_vec) - pow(sphere->diameter / 2, 2);
	eq.discriminant = eq.b * eq.b - eq.c / eq.a;
	if (eq.discriminant < 0)
		return (false);
	hp->dist = -eq.b - sqrt(eq.discriminant);
	if (hp->dist <= EPSILON)
		hp->dist = -eq.b + sqrt(eq.discriminant);
	if (hp->dist <= EPSILON)
		return (false);
	hp->type = OBJ_SPH;
	hp->obj = sphere;
	hp->loc = vec3_add(ray->origin, vec3_scale(ray->direction, hp->dist));
	hp->norm = vec3_unit(vec3_sub(hp->loc, sphere->pos));
	if (vec3_dot(ray->direction, hp->norm) > 0)
		hp->norm = vec3_scale(hp->norm, -1);
	return (true);
}

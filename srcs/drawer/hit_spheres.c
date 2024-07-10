/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/10 23:32:33 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_sphere(t_sphere *sphere, t_ray *ray);

void	hit_spheres(const t_list *spheres, t_ray *ray)
{
	t_sphere	*sphere;
	t_ray		temp;

	temp = *ray;
	while (spheres)
	{
		sphere = (t_sphere *)spheres->blk;
		if (hit_sphere(sphere, &temp) == true
			&& (temp.dist < ray->dist || ray->type == OBJ_NONE))
		{
			ray->type = OBJ_SPH;
			ray->obj = temp.obj;
			ray->dist = temp.dist;
			ray->h_point = temp.h_point;
			ray->hp_norm = temp.hp_norm;
		}
		spheres = spheres->next;
	}
}

static bool	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_vec3	sp_vec;

	sp_vec = vec3_sub(ray->origin, sphere->pos);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(sp_vec, ray->direction);
	c = vec3_dot(sp_vec, sp_vec) - pow(sphere->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	ray->dist = (-b - sqrt(discriminant)) / (2 * a);
	if (ray->dist <= EPSILON)
		ray->dist = (-b + sqrt(discriminant)) / (2 * a);
	if (ray->dist <= EPSILON)
		return (false);
	ray->h_point = vec3_add(ray->origin, vec3_scale(ray->direction, ray->dist));
	ray->hp_norm = vec3_unit(vec3_sub(ray->h_point, sphere->pos));
	if (vec3_dot(ray->direction, ray->hp_norm) > 0)
		ray->hp_norm = vec3_scale(ray->hp_norm, -1);
	ray->obj = sphere;
	return (true);
}

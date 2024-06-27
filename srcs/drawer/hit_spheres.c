/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/28 11:29:49 by dshatilo         ###   ########.fr       */
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
			ray->dist = temp.dist;
			ray->type = temp.type;
			ray->obj = temp.obj;
		}
		spheres = spheres->next;
	}
}

// struct s_quadratic_coefs
// {
// 	float		a;
// 	float		b;
// 	float		c;
// 	float		discriminant;
// };
// typedef struct s_quadratic_coefs	t_quadratic_coefs;

static bool	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_vec3	sp_vec;

	sp_vec = vec3_sub(ray->origin, sphere->pos);
	a = dot(ray->direction, ray->direction);
	b = 2.0 * dot(sp_vec, ray->direction);
	c = dot(sp_vec, sp_vec) - pow(sphere->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	ray->dist = (-b - sqrt(discriminant)) / (2 * a);
	if (ray->dist <= EPSILON)
		ray->dist = (-b + sqrt(discriminant)) / (2 * a);
	if (ray->dist <= EPSILON)
		return (false);
	ray->type = OBJ_SPH;
	ray->obj = sphere;
	return (true);
}

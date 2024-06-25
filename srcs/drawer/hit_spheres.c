/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:55:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/25 11:44:19 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_sphere(t_sphere *sphere, t_pixel *pix,
				const t_vec3 *camera_pos);

void	hit_spheres(const t_list *spheres, t_pixel *pixel,
			const t_vec3 *camera_pos)
{
	t_sphere	*sphere;
	t_pixel		temp;

	temp = *pixel;
	while (spheres)
	{
		sphere = (t_sphere *)spheres->blk;
		if (hit_sphere(sphere, &temp, camera_pos) == true
			&& (temp.dist < pixel->dist || pixel->dist == -1))
		{
			pixel->dist = temp.dist;
			pixel->type = temp.type;
			pixel->obj = temp.obj;
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

static bool	hit_sphere(t_sphere *sphere, t_pixel *pix, const t_vec3 *camera_pos)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_vec3	sp_vec;

	sp_vec = vec3_sub(*camera_pos, sphere->pos);
	a = dot(pix->r_vec, pix->r_vec);
	b = 2.0 * dot(sp_vec, pix->r_vec);
	c = dot(sp_vec, sp_vec) - pow(sphere->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	pix->dist = (-b - sqrt(discriminant)) / (2 * a);
	if (pix->dist <= EPSILON)
		pix->dist = (-b + sqrt(discriminant)) / (2 * a);
	if (pix->dist <= EPSILON)
		return (false);
	pix->type = OBJ_SPH;
	pix->obj = sphere;
	return (true);
}


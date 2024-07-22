/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:03:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/22 11:35:35 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_color_sphere(t_hp *hp, t_sphere *sph);
t_color	get_color_plane(t_hp *hp, t_plane *pln);
t_color	get_color_conic(t_hp *hp, t_conic *conic);

uint32_t	get_color(t_scene *scene, t_ray *ray)
{
	t_color	color;
	t_hp	*hp;

	hp = &ray->hp;
	if (ray->hp.type == OBJ_NONE)
		return (0xFF);
	else if (ray->hp.type == OBJ_SPH)
		color = get_color_sphere(hp, (t_sphere *)hp->obj);
	else if (ray->hp.type == OBJ_PLN)
		color = get_color_plane(hp, (t_plane *)hp->obj);
	else
		color = get_color_conic(hp, (t_conic *)hp->obj);
	color = add_lights(ray, scene, color);
	return (color_to_int(color));
}

t_color	get_color_sphere(t_hp *hp, t_sphere *sph)
{
	float	phi;
	float	theta;
	int		x;
	int		y;

	if (sph->checker_size == 0 && sph->texture)
		return (sph->color);
	phi = atan2(hp->norm.z, hp->norm.x) / (2.0 * M_PI) * sph->diameter;
	theta = asin(hp->norm.y) / M_PI * sph->diameter;
	if (sph->texture)
		return (color_prod(sph->color, sph->color));
	x = phi / sph->checker_size;
	y = theta / sph->checker_size;
	if (phi < 0)
		x++;
	if (theta < 0)
		y++;
	if ((x + y) % 2 == 0)
		return (color_invert(sph->color));
	return (sph->color);
}

t_color	get_color_plane(t_hp *hp, t_plane *pln)
{
	float	v;
	float	u;
	int		x;
	int		y;
	t_vec3	e;

	if (pln->checker_size <= 0 && !pln->texture)
		return (pln->color);
	e = vec3_unit(vec3_cross(pln->normal, (t_vec3){1, 0, 0}));
	if (sqrt(vec3_dot2(e)) < 0.01)
		e = vec3_unit(vec3_cross(pln->normal, (t_vec3){0, 0, 1}));
	u = vec3_dot(hp->pos, e);
	e = vec3_unit(vec3_cross(pln->normal, e));
	v = vec3_dot(hp->pos, e);
	if (pln->texture)
		return (color_prod(pln->color, pln->color));
	x = u / pln->checker_size;
	y = v / pln->checker_size;
	if (u < 0)
		x++;
	if (v < 0)
		y++;
	if ((x + y) % 2 == 0)
		return (color_invert(pln->color));
	return (pln->color);
}

t_color	get_color_conic(t_hp *hp, t_conic *conic)
{
	float	angle;
	float	u;
	float	v;
	int		x;
	int		y;

	if (hp->surf_type == BASE)
		return (get_color_plane(hp, (t_plane *)conic));
	if (conic->checker_size <= 0 && !conic->texture)
		return (conic->color);
	angle = vec3_dot(vec3_unit(vec3_cross(vec3_scale(conic->axis, -1),
					(t_vec3){0, 0, 1})), hp->norm);
	u = acos(angle) * conic->diameter * 2 / M_PI;
	v = vec3_dot(vec3_sub(hp->pos, conic->pos), conic->axis)
		/ (1 - vec3_dot(hp->norm, conic->axis));
	if (conic->texture)
		return (color_prod(conic->color, conic->color));
	x = u / conic->checker_size;
	y = v / conic->checker_size;
	if (u < 0)
		x++;
	if (v < 0)
		y++;
	if ((y + x) % 2 == 0)
		return (color_invert(conic->color));
	return (conic->color);
}

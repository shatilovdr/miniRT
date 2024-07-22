/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:03:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/22 14:31:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_color_sphere(t_hp *hp, t_sphere *sph);
t_color	get_color_plane(t_hp *hp, t_plane *pln);
t_color	get_color_conic(t_hp *hp, t_conic *conic);
t_color	handle_checker_and_texture(t_coord coord,
			const mlx_image_t *texture, t_color color, float checker_size);

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
	t_coord	coord;

	if (sph->checker_size == 0 && !sph->texture)
		return (sph->color);
	coord.loc_x = atan2(hp->norm.z, hp->norm.x) / (2.0 * M_PI) * sph->diameter;
	coord.loc_y = asin(hp->norm.y) / M_PI * sph->diameter;
	return (handle_checker_and_texture(
			coord, sph->texture, sph->color, sph->checker_size));
}

t_color	get_color_plane(t_hp *hp, t_plane *pln)
{
	t_coord	coord;
	t_vec3	e;

	if (pln->checker_size <= 0 && !pln->texture)
		return (pln->color);
	e = vec3_unit(vec3_cross(pln->normal, (t_vec3){1, 0, 0}));
	if (sqrt(vec3_dot2(e)) < 0.01)
		e = vec3_unit(vec3_cross(pln->normal, (t_vec3){0, 0, 1}));
	coord.loc_x = vec3_dot(hp->pos, e);
	e = vec3_unit(vec3_cross(pln->normal, e));
	coord.loc_y = vec3_dot(hp->pos, e);
	return (handle_checker_and_texture(
			coord, pln->texture, pln->color, pln->checker_size));
}

t_color	get_color_conic(t_hp *hp, t_conic *conic)
{
	t_coord	coord;
	float	angle;

	if (hp->surf_type == BASE)
		return (get_color_plane(hp, (t_plane *)conic));
	if (conic->checker_size <= 0 && !conic->texture)
		return (conic->color);
	angle = vec3_dot(vec3_unit(vec3_cross(vec3_scale(conic->axis, -1),
					(t_vec3){0, 0, 1})), hp->norm);
	coord.loc_x = acos(angle) * conic->diameter * 2 / M_PI;
	coord.loc_y = vec3_dot(vec3_sub(hp->pos, conic->pos), conic->axis)
		/ (1 - vec3_dot(hp->norm, conic->axis));
	return (handle_checker_and_texture(
			coord, conic->texture, conic->color, conic->checker_size));
}

t_color	handle_checker_and_texture(t_coord coord,
	const mlx_image_t *texture, t_color color, float checker_size)
{
	int	x;
	int	y;

	if (texture)
		color = get_texture_color(coord, texture);
	if (checker_size == 0)
		return (color);
	x = coord.loc_x / checker_size;
	y = coord.loc_y / checker_size;
	if (coord.loc_x < 0)
		x++;
	if (coord.loc_y < 0)
		y++;
	if ((x + y) % 2 == 0)
		return (color_invert(color));
	return (color);
}

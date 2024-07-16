/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:19:26 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/16 17:03:37 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool		is_in_shadow(t_light *light, t_ray *ray, t_scene *scene);
static t_color	apply_phong_model(t_scene *scene, t_ray *ray, t_light *target);

t_color	add_lights(t_ray *ray, t_scene *scene, t_color obj_color)
{
	t_color			color;
	t_color			phong;
	const t_list	*lights;
	t_light			*light;

	lights = scene->lights;
	color = color_scale(scene->amb->color, scene->amb->ratio);
	while (lights)
	{
		light = (t_light *)lights->blk;
		if (!is_in_shadow(light, ray, scene))
		{
			phong = apply_phong_model(scene, ray, light);
			color = color_add(color, phong);
		}
		lights = lights->next;
	}
	color = color_prod(obj_color, color);
	return (color);
}

bool	is_in_shadow(t_light *light, t_ray *ray, t_scene *scene)
{
	t_ray	light_ray;

	light_ray.direction = vec3_unit(vec3_sub(ray->h_point, light->pos));
	light_ray.origin = light->pos;
	hit_objects(scene, &light_ray);
	if (light_ray.type != OBJ_NONE
		&& vec3_equals(&light_ray.h_point, &ray->h_point) == false)
		return (true);
	return (false);
}

static t_color	apply_phong_model(t_scene *scene, t_ray *ray, t_light *light)
{
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	t_vec3	light_dir;
	float	specular;
	float	diffuse;

	light_dir = vec3_unit(vec3_sub(light->pos, ray->h_point));
	diffuse = vec3_dot(light_dir, ray->hp_norm);
	view_dir = vec3_unit(vec3_sub(ray->h_point, scene->cam->pos));
	reflect_dir = vec3_unit(vec3_sub(light_dir,
				vec3_scale(ray->hp_norm, 2.0f * diffuse)));
	specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 32);
	return (
		color_scale(light->color, (specular + diffuse) * light->brightness));
}

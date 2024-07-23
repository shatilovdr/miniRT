/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:43:04 by ivalimak          #+#    #+#             */
/*   Updated: 2024/06/24 21:25:35 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_amb_light	*parse_alight(const char *line, const t_scene *scene)
{
	t_amb_light	*out;
	long double	ratio;
	t_color		color;

	out = ft_push(ft_alloc(sizeof(*out)));
	if (!out)
	{
		close(scene->fd);
		ft_exit(rt_perror());
	}
	line++;
	ratio = getld(&line, (long double [2]){0.0, 1.0});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	ft_memcpy(out, &(t_amb_light){.ratio = ratio, .color = color},
		sizeof(*out));
	return (out);
}

t_camera	*parse_camera(const char *line, const t_scene *scene)
{
	t_camera	*out;
	t_vec3		vecs[2];
	uint8_t		fov;

	out = ft_push(ft_alloc(sizeof(*out)));
	if (!out)
	{
		close(scene->fd);
		ft_exit(rt_perror());
	}
	line++;
	ft_memcpy(&vecs[0], getvec3(&line, (long double [2]){POS_MIN, POS_MAX}),
		sizeof(vecs[0]));
	ft_memcpy(&vecs[1], getvec3(&line, (long double [2]){-1.0, 1.0}),
		sizeof(vecs[1]));
	fov = getu8(&line, (uint8_t [2]){0, 180});
	ft_memcpy(out, &(t_camera){.pos = vecs[0], .orientation = vecs[1],
		.fov = fov}, sizeof(*out));
	return (out);
}

t_light	*parse_light(const char *line, const t_scene *scene)
{
	t_light		*out;
	t_vec3		pos;
	long double	brightness;
	t_color		color;

	out = ft_push(ft_alloc(sizeof(*out)));
	if (!out)
	{
		close(scene->fd);
		ft_exit(rt_perror());
	}
	line++;
	ft_memcpy(&pos, getvec3(&line, (long double [2]){POS_MIN, POS_MAX}),
		sizeof(pos));
	brightness = getld(&line, (long double [2]){0.0, 1.0});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	ft_memcpy(out, &(t_light){.pos = pos, .brightness = brightness,
		.color = color}, sizeof(*out));
	return (out);
}

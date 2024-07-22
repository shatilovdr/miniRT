/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:43:04 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/22 22:41:17 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

t_amb_light	*parse_alight(const char *line)
{
	t_amb_light	*out;
	long double	ratio;
	t_color		color;

	line++;
	ratio = getld(&line, (long double [2]){0.0, 1.0});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	out = ft_memcpy(ft_push(ft_alloc(sizeof(*out))),
			&(t_amb_light){.ratio = ratio, .color = color},
			sizeof(*out));
	if (!out)
		rt_exit(rt_perror());
	return (out);
}

t_camera	*parse_camera(const char *line)
{
	t_camera	*out;
	t_vec3		vecs[2];
	uint8_t		fov;

	line++;
	vecs[0] = getvec3(&line, (long double [2]){POS_MIN, POS_MAX});
	vecs[1] = getvec3(&line, (long double [2]){-1.0, 1.0});
	fov = getu8(&line, (uint8_t [2]){0, 180});
	out = ft_memcpy(ft_push(ft_alloc(sizeof(*out))),
			&(t_camera){.pos = vecs[0], .orientation = vecs[1], .fov = fov},
			sizeof(*out));
	if (!out)
		rt_exit(rt_perror());
	return (out);
}

t_light	*parse_light(const char *line)
{
	t_light		*out;
	t_vec3		pos;
	long double	brightness;
	t_color		color;

	line++;
	pos = getvec3(&line, (long double [2]){POS_MIN, POS_MAX});
	brightness = getld(&line, (long double [2]){0.0, 1.0});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	out = ft_memcpy(ft_push(ft_alloc(sizeof(*out))),
			&(t_light){.pos = pos, .brightness = brightness, .color = color},
			sizeof(*out));
	if (!out)
		rt_exit(rt_perror());
	return (out);
}

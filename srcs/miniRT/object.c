/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:22:30 by ivalimak          #+#    #+#             */
/*   Updated: 2024/05/28 00:17:56 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

t_cylinder	*parse_cyl(const char *line)
{
	t_cylinder	*out;
	t_vec3		vecs[2];
	long double	dims[2];
	t_color		color;

	out = ft_push(ft_alloc(sizeof(*out)));
	if (!out)
		ft_exit(rt_perror());
	line += 2;
	ft_memcpy(&vecs[0], getvec3(&line, (long double [2]){POS_MIN, POS_MAX}),
		sizeof(vecs[0]));
	ft_memcpy(&vecs[1], getvec3(&line, (long double [2]){-1.0, 1.0}),
		sizeof(vecs[1]));
	dims[0] = getld(&line, (long double [2]){0.0, LDBL_MAX});
	dims[1] = getld(&line, (long double [2]){0.0, LDBL_MAX});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	ft_memcpy(out, &(t_cylinder){.pos = vecs[0], .axis = vecs[1],
		.diameter = dims[0], .height = dims[1], .color = color}, sizeof(*out));
	return (out);
}

t_sphere	*parse_sph(const char *line)
{
	t_sphere	*out;
	t_vec3		pos;
	long double	diameter;
	t_color		color;

	out = ft_push(ft_alloc(sizeof(*out)));
	if (!out)
		ft_exit(rt_perror());
	line += 2;
	ft_memcpy(&pos, getvec3(&line, (long double [2]){POS_MIN, POS_MAX}),
		sizeof(pos));
	diameter = getld(&line, (long double [2]){0.0, LDBL_MAX});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	ft_memcpy(out, &(t_sphere){.pos = pos, .diameter = diameter,
		.color = color}, sizeof(*out));
	return (out);
}

t_plane	*parse_pln(const char *line)
{
	t_plane	*out;
	t_vec3	vecs[2];
	t_color	color;

	out = ft_push(ft_alloc(sizeof(*out)));
	if (!out)
		ft_exit(rt_perror());
	line += 2;
	ft_memcpy(&vecs[0], getvec3(&line, (long double [2]){POS_MIN, POS_MAX}),
		sizeof(vecs[0]));
	ft_memcpy(&vecs[1], getvec3(&line, (long double [2]){-1.0, 1.0}),
		sizeof(vecs[1]));
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	ft_memcpy(out, &(t_plane){.pos = vecs[0], .normal = vecs[1],
		.color = color}, sizeof(*out));
	return (out);
}

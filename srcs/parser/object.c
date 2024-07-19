/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:22:30 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/19 17:53:19 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

static inline float	_getcbsize(const char **line);

t_cylinder	*parse_cyl(const char *line, const t_scene *scene)
{
	t_cylinder	*out;
	t_vec3		vecs[2];
	long double	dims[3];
	mlx_image_t	*texture;
	t_color		color;

	line += 2;
	vecs[0] = getvec3(&line, (long double [2]){POS_MIN, POS_MAX});
	vecs[1] = getvec3(&line, (long double [2]){-1.0, 1.0});
	dims[0] = getld(&line, (long double [2]){0.0, LDBL_MAX});
	dims[1] = getld(&line, (long double [2]){0.0, LDBL_MAX});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	dims[2] = _getcbsize(&line);
	texture = gettexture(&line);
	out = ft_memcpy(ft_push(ft_alloc(sizeof(*out))),
			&(t_cylinder){.pos = vecs[0], .axis = vecs[1], .diameter = dims[0],
			.height = dims[1], .color = color, .cbsize = (float)dims[2]},
			sizeof(*out));
	if (!out)
	{
		close(scene->fd);
		ft_exit(rt_perror());
	}
	out->texture = texture;
	return (out);
}

t_sphere	*parse_sph(const char *line, const t_scene *scene)
{
	t_sphere	*out;
	t_vec3		pos;
	long double	dims[2];
	mlx_image_t	*texture;
	t_color		color;

	line += 2;
	pos = getvec3(&line, (long double [2]){POS_MIN, POS_MAX});
	dims[0] = getld(&line, (long double [2]){0.0, LDBL_MAX});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	dims[1] = _getcbsize(&line);
	texture = gettexture(&line);
	out = ft_memcpy(ft_push(ft_alloc(sizeof(*out))), &(t_sphere){.pos = pos,
			.diameter = dims[0], .color = color, .cbsize = dims[1]},
			sizeof(*out));
	if (!out)
	{
		close(scene->fd);
		ft_exit(rt_perror());
	}
	out->texture = texture;
	return (out);
}

t_plane	*parse_pln(const char *line, const t_scene *scene)
{
	t_plane		*out;
	float		cbsize;
	t_vec3		vecs[2];
	mlx_image_t	*texture;
	t_color		color;

	line += 2;
	vecs[0] = getvec3(&line, (long double [2]){POS_MIN, POS_MAX});
	vecs[1] = getvec3(&line, (long double [2]){-1.0, 1.0});
	ft_memcpy(&color, getcolor(&line, (uint8_t [2]){0, 255}), sizeof(color));
	cbsize = _getcbsize(&line);
	texture = gettexture(&line);
	out = ft_memcpy(ft_push(ft_alloc(sizeof(*out))), &(t_plane){.pos = vecs[0],
			.normal = vecs[1], .color = color, .cbsize = cbsize}, sizeof(*out));
	if (!out)
	{
		close(scene->fd);
		ft_exit(rt_perror());
	}
	out->texture = texture;
	return (out);
}

static inline float	_getcbsize(const char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (ft_isdigit(**line))
		return (getld(line, (long double [2]){0.0, FLT_MAX}));
	return (0.0);
}

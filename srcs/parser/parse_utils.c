/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:37:20 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/24 16:28:24 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

mlx_image_t	*gettexture(const char **line)
{
	mlx_texture_t	*texture;
	mlx_image_t		*out;

	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		return (NULL);
	if (!ft_strequals(&(*line)[ft_max(ft_strlen(*line) - 4, 0)], ".png"))
		rt_exit(rt_ferror("Unsupported image format"));
	texture = mlx_load_png(*line);
	if (!texture)
		rt_exit(rt_ferror(ft_push(ft_strnjoin(3,
						*line, ": ", mlx_strerror(mlx_errno)))));
	out = mlx_texture_to_image(getmlx(), texture);
	mlx_delete_texture(texture);
	if (!out)
		rt_exit(rt_ferror(ft_push(ft_strnjoin(3,
						*line, ": ", mlx_strerror(mlx_errno)))));
	return (out);
}

long double	getld(const char **line, const long double range[2])
{
	long double	out;
	const char	*nbr;

	if (!**line)
		return (0.0);
	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		rt_exit(rt_ferror("Unexpected EOL"));
	nbr = ft_push(ft_substr(*line, 0, ft_strclen(*line, ' ')));
	if (!nbr)
		rt_exit(rt_perror());
	if (!ft_isfloat(nbr))
		rt_exit(rt_ferror("Invalid value"));
	out = ft_atof32(nbr);
	if (out < range[0] || out > range[1])
		rt_exit(rt_ferror("Value out of range"));
	*line += ft_strlen(nbr);
	ft_popblk(nbr);
	return (out);
}

uint8_t	getu8(const char **line, const uint8_t range[2])
{
	uint8_t		out;
	const char	*nbr;

	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		rt_exit(rt_ferror("Unexpected EOL"));
	nbr = ft_push(ft_substr(*line, 0, ft_strclen(*line, ' ')));
	if (!nbr)
		rt_exit(rt_perror());
	if (!ft_isuint(nbr, 1))
		rt_exit(rt_ferror("Invalid value"));
	out = ft_atou8(nbr);
	if (out < range[0] || out > range[1])
		rt_exit(rt_ferror("Value out of range"));
	*line += ft_strlen(nbr);
	ft_popblk(nbr);
	return (out);
}

t_color	*getcolor(const char **line, const uint8_t range[2])
{
	static t_color	out;
	const char		**vals;

	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		rt_exit(rt_ferror("Unexpected EOL"));
	vals = ft_pusharr(ft_split(
				ft_substr(*line, 0, ft_strclen(*line, ' ')), ','));
	if (!vals)
		rt_exit(rt_perror());
	if (ft_getblksize(vals) / 4 != sizeof(*vals) || !ft_isuint(vals[0], 1)
		|| !ft_isuint(vals[1], 1) || !ft_isuint(vals[2], 1))
		rt_exit(rt_ferror("Invalid value"));
	ft_memset(&out, 0, sizeof(out));
	ft_memcpy(&out, &(t_color){.r = ft_atou8(vals[0]),
		.g = ft_atou8(vals[1]), .b = ft_atou8(vals[2])}, sizeof(out));
	if (out.r < range[0] || out.r > range[1] || out.g < range[0]
		|| out.g > range[1] || out.b < range[0] || out.b > range[1])
		rt_exit(rt_ferror("Value out of range"));
	*line += ft_strlen(vals[0]) + ft_strlen(vals[1]) + ft_strlen(vals[2]) + 2;
	ft_popblks(4, vals, vals[0], vals[1], vals[2]);
	return (&out);
}

t_vec3	getvec3(const char **line, const long double range[2])
{
	t_vec3		out;
	const char	**vals;

	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		rt_exit(rt_ferror("Unexpected EOL"));
	vals = ft_pusharr(ft_split(
				ft_substr(*line, 0, ft_strclen(*line, ' ')), ','));
	if (!vals)
		rt_exit(rt_perror());
	if (ft_getblksize(vals) / 4 != sizeof(*vals) || !ft_isfloat(vals[0])
		|| !ft_isfloat(vals[1]) || !ft_isfloat(vals[2]))
		rt_exit(rt_ferror("Invalid value"));
	out.x = ft_atof32(vals[0]);
	out.y = ft_atof32(vals[1]);
	out.z = ft_atof32(vals[2]);
	if (out.x < range[0] || out.x > range[1] || out.y < range[0]
		|| out.y > range[1] || out.z < range[0] || out.z > range[1])
		rt_exit(rt_ferror("Value out of range"));
	*line += ft_strlen(vals[0]) + ft_strlen(vals[1]) + ft_strlen(vals[2]) + 2;
	ft_popblks(4, vals, vals[0], vals[1], vals[2]);
	return (out);
}

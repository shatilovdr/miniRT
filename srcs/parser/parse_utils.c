/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:37:20 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/19 17:48:37 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "ft_stdio/ft_printf.h"

mlx_image_t	*gettexture(const char **line)
{
	static mlx_t	*mlx = NULL;
	mlx_texture_t	*texture;
	mlx_image_t		*out;

	if (!mlx)
		mlx = mlx_init(1920, 1080, "Fuck", true);
	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		return (NULL);
	if (!ft_strequals(&(*line)[ft_max(ft_strlen(*line) - 4, 0)], ".png"))
		ft_exit(rt_ferror("Unsupported image format"));
	texture = mlx_load_png(*line);
	if (!texture)
		ft_exit(rt_ferror(mlx_strerror(mlx_errno)));
	out = mlx_texture_to_image(mlx, texture);
	if (!out)
		ft_exit(rt_ferror(mlx_strerror(mlx_errno)));
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
		ft_exit(rt_ferror("Unexpected EOL"));
	nbr = ft_push(ft_substr(*line, 0, ft_strclen(*line, ' ')));
	if (!nbr)
		ft_exit(rt_perror());
	if (!ft_isfloat(nbr))
		ft_exit(rt_ferror("Invalid value"));
	out = ft_atof80(nbr);
	if (out < range[0] || out > range[1])
		ft_exit(rt_ferror("Value out of range"));
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
		ft_exit(rt_ferror("Unexpected EOL"));
	nbr = ft_push(ft_substr(*line, 0, ft_strclen(*line, ' ')));
	if (!nbr)
		ft_exit(rt_perror());
	if (!ft_isuint(nbr, 1))
		ft_exit(rt_ferror("Invalid value"));
	out = ft_atou8(nbr);
	if (out < range[0] || out > range[1])
		ft_exit(rt_ferror("Value out of range"));
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
		ft_exit(rt_ferror("Unexpected EOL"));
	vals = ft_pusharr(ft_split(
				ft_substr(*line, 0, ft_strclen(*line, ' ')), ','));
	if (!vals)
		ft_exit(rt_perror());
	if (ft_getblksize(vals) / 4 != sizeof(*vals) || !ft_isuint(vals[0], 1)
		|| !ft_isuint(vals[1], 1) || !ft_isuint(vals[2], 1))
		ft_exit(rt_ferror("Invalid value"));
	ft_memcpy(&out, &(t_color){.r = ft_atou8(vals[0]),
		.g = ft_atou8(vals[1]), .b = ft_atou8(vals[2])}, sizeof(out));
	if (out.r < range[0] || out.r > range[1] || out.g < range[0]
		|| out.g > range[1] || out.b < range[0] || out.b > range[1])
		ft_exit(rt_ferror("Value out of range"));
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
		ft_exit(rt_ferror("Unexpected EOL"));
	vals = ft_pusharr(ft_split(
				ft_substr(*line, 0, ft_strclen(*line, ' ')), ','));
	if (!vals)
		ft_exit(rt_perror());
	if (ft_getblksize(vals) / 4 != sizeof(*vals) || !ft_isfloat(vals[0])
		|| !ft_isfloat(vals[1]) || !ft_isfloat(vals[2]))
		ft_exit(rt_ferror("Invalid value"));
	ft_memcpy(&out, &(t_vec3){.x = ft_atof80(vals[0]),
		.y = ft_atof80(vals[1]), .z = ft_atof80(vals[2])}, sizeof(out));
	if (out.x < range[0] || out.x > range[1] || out.y < range[0]
		|| out.y > range[1] || out.z < range[0] || out.z > range[1])
		ft_exit(rt_ferror("Value out of range"));
	*line += ft_strlen(vals[0]) + ft_strlen(vals[1]) + ft_strlen(vals[2]) + 2;
	ft_popblks(4, vals, vals[0], vals[1], vals[2]);
	return (out);
}

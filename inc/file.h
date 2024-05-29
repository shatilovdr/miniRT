/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:25:02 by ivalimak          #+#    #+#             */
/*   Updated: 2024/05/29 10:42:05 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H
# include "libft.h"
# include "types.h"
# include "rt_error.h"
# include <fcntl.h>
# include <float.h>
# include <unistd.h>

# define OBJ_SPH 0
# define OBJ_PLN 1
# define OBJ_CYL 2

# define POS_MAX 42000.0L
# define POS_MIN -42000.0L

// file.c
t_scene		*parsefile(const char *path);

// element.c
t_amb_light	*parse_alight(const char *line, const t_scene *scene);
t_camera	*parse_camera(const char *line, const t_scene *scene);
t_light		*parse_light(const char *line, const t_scene *scene);

// object.c
t_cylinder	*parse_cyl(const char *line, const t_scene *scene);
t_sphere	*parse_sph(const char *line, const t_scene *scene);
t_plane		*parse_pln(const char *line, const t_scene *scene);

// parse_utils.c
long double	getld(const char **line, const long double range[2]);
uint8_t		getu8(const char **line, const uint8_t range[2]);
t_color		*getcolor(const char **line, const uint8_t range[2]);
t_vec3		*getvec3(const char **line, const long double range[2]);

#endif

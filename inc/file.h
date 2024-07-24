/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:25:02 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/23 15:08:36 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H
# include "types.h"
# include "rt_error.h"
# include <fcntl.h>

# define OBJ_NONE -1
# define OBJ_LGT 0
# define OBJ_SPH 1
# define OBJ_PLN 2
# define OBJ_CON 3

# define POS_MAX 42000.0
# define POS_MIN -42000.0

# define SCENE_CLOSED -2

// file.c
t_scene		*parsefile(const char *path);

// element.c
t_amb_light	*parse_alight(const char *line);
t_camera	*parse_camera(const char *line);
t_light		*parse_light(const char *line);

// object.c
t_sphere	*parse_sph(const char *line);
t_plane		*parse_pln(const char *line);
t_conic		*parse_con(const char *line);

// file_utils.c
int32_t		openscene(const char *path);
int32_t		getscene(void);
void		closescene(void);

// parse_utils.c
mlx_image_t	*gettexture(const char **line);
long double	getld(const char **line, const long double range[2]);
uint8_t		getu8(const char **line, const uint8_t range[2]);
t_color		*getcolor(const char **line, const uint8_t range[2]);
t_vec3		getvec3(const char **line, const long double range[2]);

#endif

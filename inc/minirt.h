/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:51:00 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/19 15:08:09 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "ft_stdio/ft_printf.h"
# include "types.h"
# include "MLX42/MLX42.h"

// error.c
int32_t		rt_perror(void);
int32_t		rt_ferror(const char *err);


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


// vec3_operations.c
t_vec3		vec3(double x, double y, double z);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_prod(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(double n, t_vec3 p);

// vec3_multiplication.c
double		dot(t_vec3 a, t_vec3 b);
double		dot2(t_vec3 a);
t_vec3		cross(t_vec3 a, t_vec3 b);

// vec3_rotation.c
t_vec3		rotate_x(t_vec3 vec, double angle);
t_vec3		rotate_y(t_vec3 vec, double angle);
t_vec3		rotate_z(t_vec3 vec, double angle);

// vec3_operations2.c
double		vec3_norm(t_vec3 v);
t_vec3		vec3_unit(t_vec3 p);
double		vec3_cos(t_vec3 a, t_vec3 b);
double		vec3_sin(t_vec3 a, t_vec3 b);
double		distance(t_vec3 p1, t_vec3 p2);

// draw_scene.c
int			draw_scene(t_scene *scene);

//prepare_scene.c
void		prepare_img(t_scene *scene);

//transform_scene.c
void		transform_scene(t_scene *scene);

// objects_to_image.c
int			objects_to_image(t_scene *scene);

#endif
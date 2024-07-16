/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:51:00 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/16 17:45:22 by dshatilo         ###   ########.fr       */
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

# define OBJ_NONE -1
# define OBJ_SPH 0
# define OBJ_PLN 1
# define OBJ_CYL 2

# define POS_MAX 42000.0L
# define POS_MIN -42000.0L

# define WIDTH 1280
# define HEIGHT 720

# define EPSILON 0.00001

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
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 v, float coef);
float		vec3_dot(t_vec3 a, t_vec3 b);
float		vec3_norm(t_vec3 v);


// vec3_operations2.c
t_vec3		vec3_unit(t_vec3 p);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
bool		vec3_equals(t_vec3 *a, t_vec3 *b);
float		vec3_distance(t_vec3 a, t_vec3 b);

// draw_scene.c
int			draw_scene(t_scene *scene);

// calculate_img.c
void		calculate_img(t_scene *scene);

// init_transform.c
t_transform	init_transform(t_scene *scene);

// get_ray_direction.c
t_vec3		get_ray_direction(t_scene *scene, t_transform *t, int x, int y);

// hit_objects.c
void		hit_objects(t_scene *scene, t_ray *ray);

// hit_spheres.c
void		hit_spheres(const t_list *spheres, t_ray *ray);

// hit_planes.c
void		hit_planes(const t_list *planes, t_ray *ray);

// get_color.c
uint32_t	get_color(t_scene *scene, t_ray *ray);

// color_alg.c
t_color		color_scale(t_color color, float scale);
t_color		color_add(t_color a, t_color b);
t_color		color_prod(t_color a, t_color b);
uint32_t	color_to_int(t_color color);

// add_lights.c
t_color		add_lights(t_ray *ray, t_scene *scene, t_color obj_color);

#endif
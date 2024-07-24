/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:51:00 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/23 15:08:31 by ivalimak         ###   ########.fr       */
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
# include "file.h"
# include "types.h"
# include "MLX42.h"

# define WIDTH 1280
# define HEIGHT 720

# define EPSILON 0.00001

# define BASE 0
# define CURVED 1

// main.c
void		rt_exit(const int32_t estat);

// utils.c
mlx_t		*getmlx(void);

// vec3_operations.c
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 v, float coef);
float		vec3_dot(t_vec3 a, t_vec3 b);
float		vec3_dot2(t_vec3 a);

// vec3_operations2.c
float		vec3_norm(t_vec3 v);
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
bool		hit_plane(const t_plane *plane, t_ray *ray, t_hp *hp);

// hit_conics.c
void		hit_base(t_conic *c, t_ray *ray, t_hp *hp, t_vec3 shift);
t_hp		*select_closest_hp(t_hp *a, t_hp *b);
void		check_conic_intersection(
				t_conic *conic, t_ray *ray, t_quad_eq *eq, t_hp *hp);

// hit_cylinders.c
void		hit_cylinders(const t_list *cylinders, t_ray *ray);

// hit_cones.c
void		hit_cones(const t_list *cones, t_ray *ray);

// get_color.c
uint32_t	get_color(t_scene *scene, t_ray *ray);

// color_alg.c
t_color		color_scale(t_color color, float scale);
t_color		color_add(t_color a, t_color b);
t_color		color_prod(t_color a, t_color b);
uint32_t	color_to_int(t_color color);
t_color		color_invert(t_color color);

// add_lights.c
t_color		add_lights(t_ray *ray, t_scene *scene, t_color obj_color);

// get_texture_color.c
t_color	get_texture_color(t_coord coord, const mlx_image_t *img);

#endif

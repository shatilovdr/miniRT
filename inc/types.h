/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:25:43 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/22 13:02:30 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "libft.h"
# include "MLX42/MLX42.h"

typedef struct s_amb_light	t_amb_light;
typedef struct s_conic		t_conic;
typedef struct s_camera		t_camera;
typedef struct s_sphere		t_sphere;
typedef struct s_light		t_light;
typedef struct s_plane		t_plane;
typedef struct s_vec3		t_vec3;
typedef struct s_color		t_color;
typedef struct s_transform	t_transform;
typedef struct s_coord		t_coord;
typedef struct s_hp			t_hp;
typedef struct s_ray		t_ray;
typedef struct s_quad_eq	t_quad_eq;
typedef struct s_scene		t_scene;

struct s_scene
{
	int32_t				fd;
	const t_amb_light	*amb;
	const t_camera		*cam;
	const t_list		*lights;
	const t_list		*cylinders;
	const t_list		*spheres;
	const t_list		*planes;
	const t_list		*cones;
	mlx_t				*mlx;
	mlx_image_t			*img;
};

struct s_vec3
{
	float	x;
	float	y;
	float	z;
};

struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};

struct s_amb_light
{
	const float			ratio;
	const t_color		color;
};

struct s_camera
{
	const t_vec3	pos;
	const t_vec3	orientation;
	const uint8_t	fov;
};

struct s_light
{
	const t_vec3		pos;
	const float			brightness;
	const t_color		color;
};

struct s_sphere
{
	const t_vec3		pos;
	const float			diameter;
	const t_color		color;
	const float			checker_size;
	const mlx_image_t	*texture;
};

struct s_plane
{
	const t_vec3		pos;
	const t_vec3		normal;
	const float			dummy1;
	const float			dummy2;
	const t_color		color;
	const float			checker_size;
	const mlx_image_t	*texture;
};

struct s_conic
{
	const t_vec3		pos;
	const t_vec3		axis;
	const float			diameter;
	const float			height;
	const t_color		color;
	const float			checker_size;
	const mlx_image_t	*texture;
};

struct s_transform
{
	t_vec3	yaw_axis;
	float	yaw_cos;
	float	yaw_sin;
	t_vec3	pitch_axis;
	float	pitch_cos;
	float	pitch_sin;
	float	z_dist;
};

struct s_coord
{
	float	loc_x;
	float	loc_y;
};

struct s_hp
{
	int		type;
	void	*obj;
	int		surf_type;
	double	dist;
	t_vec3	pos;
	t_vec3	norm;
};

struct s_ray
{
	t_vec3	direction;
	t_vec3	origin;
	t_hp	hp;
};

struct s_quad_eq
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
};

#endif

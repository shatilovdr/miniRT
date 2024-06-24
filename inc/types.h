/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:25:43 by ivalimak          #+#    #+#             */
/*   Updated: 2024/06/25 00:16:09 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "libft.h"
# include "MLX42/MLX42.h"

typedef struct s_amb_light	t_amb_light;
typedef struct s_cylinder	t_cylinder;
typedef struct s_camera		t_camera;
typedef struct s_sphere		t_sphere;
typedef struct s_light		t_light;
typedef struct s_plane		t_plane;
typedef struct s_vec3		t_vec3;
typedef struct s_color		t_color;
typedef struct s_scene		t_scene;

struct s_scene
{
	int32_t				fd;
	const t_amb_light	*amb;
	const t_camera		*cam;
	const t_light		*light;
	const t_list		*cylinders;
	const t_list		*spheres;
	const t_list		*planes;
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
};

struct s_plane
{
	const t_vec3	pos;
	const t_vec3	normal;
	const t_color	color;
};

struct s_cylinder
{
	const t_vec3		pos;
	const t_vec3		axis;
	const float			diameter;
	const float			height;
	const t_color		color;
};

#endif

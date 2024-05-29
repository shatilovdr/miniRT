/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_alg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:30:27 by dshatilo          #+#    #+#             */
/*   Updated: 2024/05/29 13:16:31 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIN_ALG_H
# define LIN_ALG_H
# include "minirt.h"
# include <math.h>

// vec3_operations.c
t_vec3	vec3(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_prod(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(double n, t_vec3 p);

// vec3_multiplication.c
double	dot(t_vec3 a, t_vec3 b);
double	dot2(t_vec3 a);
t_vec3	cross(t_vec3 a, t_vec3 b);

// vec3_rotation.c
t_vec3	rotate_x(t_vec3 vec, double angle);
t_vec3	rotate_y(t_vec3 vec, double angle);
t_vec3	rotate_z(t_vec3 vec, double angle);

// vec3_operations2.c
double	vec3_norm(t_vec3 v);
t_vec3	vec3_unit(t_vec3 p);
double	vec3_cos(t_vec3 a, t_vec3 b);
double	vec3_sin(t_vec3 a, t_vec3 b);
double	distance(t_vec3 p1, t_vec3 p2);

#endif

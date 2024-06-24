/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:20:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/24 21:31:25 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec3_norm(t_vec3 vect)
{
	return (sqrt(dot2(vect)));
}

t_vec3	vec3_unit(t_vec3 vect)
{
	t_vec3	unit;
	float	norm;

	norm = vec3_norm(vect);
	unit.x = vect.x / norm;
	unit.y = vect.y / norm;
	unit.z = vect.z / norm;
	return (unit);
}

float	vec3_cos(t_vec3 a, t_vec3 b)
{
	return (dot(a, b) / (vec3_norm(a) * vec3_norm(b)));
}

float	vec3_sin(t_vec3 a, t_vec3 b)
{
	return (sqrt(1 - pow(vec3_cos(a, b), 2)));
}

float	distance(t_vec3 v1, t_vec3 v2)
{
	float	d;

	d = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
	return (d);
}

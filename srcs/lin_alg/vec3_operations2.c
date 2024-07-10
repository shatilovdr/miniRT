/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:20:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/09 11:59:00 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec3_norm(t_vec3 vect)
{
	return (sqrt(vec3_dot2(vect)));
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
	return (vec3_dot(a, b) / (vec3_norm(a) * vec3_norm(b)));
}

float	vec3_sin(t_vec3 a, t_vec3 b)
{
	return (sqrt(1 - pow(vec3_cos(a, b), 2)));
}

float	vec3_distance(t_vec3 a, t_vec3 b)
{
	float	d;

	d = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
	return (d);
}

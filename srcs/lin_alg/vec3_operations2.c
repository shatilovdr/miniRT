/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:17:57 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/18 14:57:39 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec3_norm(t_vec3 vect)
{
	return (sqrt(vec3_dot(vect, vect)));
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

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	cp;

	cp.x = a.y * b.z - a.z * b.y;
	cp.y = a.z * b.x - a.x * b.z;
	cp.z = a.x * b.y - a.y * b.x;
	return (cp);
}

bool	vec3_equals(t_vec3 *a, t_vec3 *b)
{
	if (fabs(a->x - b->x) > 0.001)
		return (false);
	if (fabs(a->y - b->y) > 0.001)
		return (false);
	if (fabs(a->z - b->z) > 0.001)
		return (false);
	return (true);
}

float	vec3_distance(t_vec3 a, t_vec3 b)
{
	float	d;

	d = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
	return (d);
}

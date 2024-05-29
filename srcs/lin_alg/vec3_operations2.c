/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:20:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/05/29 12:48:08 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

double	vec3_norm(t_vec3 vect)
{
	return (sqrt(dot2(vect)));
}

t_vec3	vec3_unit(t_vec3 vect)
{
	t_vec3	unit;
	double	norm;

	norm = vec3_norm(vect);
	unit.x = vect.x / norm;
	unit.y = vect.y / norm;
	unit.z = vect.z / norm;
	return (unit);
}

double	vec3_cos(t_vec3 a, t_vec3 b)
{
	return (dot(a, b) / (vec3_norm(a) * vec3_norm(b)));
}

double	vec3_sin(t_vec3 a, t_vec3 b)
{
	return (sqrt(1 - pow(vec3_cos(a, b), 2)));
}

double	distance(t_vec3 v1, t_vec3 v2)
{
	double	d;

	d = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
	return (d);
}

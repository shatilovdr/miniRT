/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:56:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/18 14:57:32 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	diff;

	diff.x = a.x - b.x;
	diff.y = a.y - b.y;
	diff.z = a.z - b.z;
	return (diff);
}

t_vec3	vec3_scale(t_vec3 v, float coef)
{
	t_vec3	new;

	new.x = coef * v.x;
	new.y = coef * v.y;
	new.z = coef * v.z;
	return (new);
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vec3_dot2(t_vec3 a)
{
	return (vec3_dot(a, a));
}

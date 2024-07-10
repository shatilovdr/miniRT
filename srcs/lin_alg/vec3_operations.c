/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:56:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/10 21:38:37 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3(float x, float y, float z)
{
	t_vec3	vec3or;

	vec3or.x = x;
	vec3or.y = y;
	vec3or.z = z;
	return (vec3or);
}

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

t_vec3	vec3_prod(t_vec3 a, t_vec3 b)
{
	t_vec3	prod;

	prod.x = a.x * b.x;
	prod.y = a.y * b.y;
	prod.z = a.z * b.z;
	return (prod);
}

t_vec3	vec3_scale(t_vec3 v, float coef)
{
	t_vec3	new;

	new.x = coef * v.x;
	new.y = coef * v.y;
	new.z = coef * v.z;
	return (new);
}

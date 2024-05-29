/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:20:53 by dshatilo          #+#    #+#             */
/*   Updated: 2024/05/29 12:36:22 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_vec3	rotate_x(t_vec3 vec, double angle)
{
	t_vec3	row1;
	t_vec3	row2;
	t_vec3	row3;
	t_vec3	rotated;

	angle *= M_PI / 180;
	row1 = (t_vec3){1, 0, 0};
	row2 = (t_vec3){0, cos(angle), sin(angle)};
	row3 = (t_vec3){0, -sin(angle), cos(angle)};
	rotated.x = dot(vec, row1);
	rotated.y = dot(vec, row2);
	rotated.z = dot(vec, row3);
	return (rotated);
}

t_vec3	rotate_y(t_vec3 vec, double angle)
{
	t_vec3	row1;
	t_vec3	row2;
	t_vec3	row3;
	t_vec3	rotated;

	angle *= M_PI / 180;
	row1 = (t_vec3){cos(angle), 0, -sin(angle)};
	row2 = (t_vec3){0, 1, 0};
	row3 = (t_vec3){sin(angle), 0, cos(angle)};
	rotated.x = dot(vec, row1);
	rotated.y = dot(vec, row2);
	rotated.z = dot(vec, row3);
	return (rotated);
}

t_vec3	rotate_z(t_vec3 vec, double angle)
{
	t_vec3	row1;
	t_vec3	row2;
	t_vec3	row3;
	t_vec3	rotated;

	angle *= M_PI / 180;
	row1 = (t_vec3){cos(angle), sin(angle), 0};
	row2 = (t_vec3){-sin(angle), cos(angle), 0};
	row3 = (t_vec3){0, 0, 1};
	rotated.x = dot(vec, row1);
	rotated.y = dot(vec, row2);
	rotated.z = dot(vec, row3);
	return (rotated);
}

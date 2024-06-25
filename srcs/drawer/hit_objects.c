/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:13:45 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/25 11:25:03 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_objects(t_scene *scene, t_pixel *pixel)
{
	pixel->dist = -1;
	hit_spheres(scene->spheres, pixel, &scene->cam->pos);
}


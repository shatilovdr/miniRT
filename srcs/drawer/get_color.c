/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:03:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/25 17:50:10 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_color(t_scene *scene, t_pixel *pixel)
{
	t_color	color;

	(void)scene;
	color = (t_color){0};
	if (pixel->type == OBJ_SPH)
		color = (t_color){105, 245, 105};
	return (color);
}

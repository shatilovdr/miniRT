/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:39:38 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/22 10:43:20 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_scale(t_color color, float scale)
{
	color.r = color.r * scale;
	color.g = color.g * scale;
	color.b = color.b * scale;
	return (color);
}

uint32_t	color_to_int(t_color color)
{
	uint32_t	res;

	res = color.r;
	res = (res << 8) + color.g;
	res = (res << 8) + color.b;
	return (res << 8 | 0xFF);
}

t_color	color_add(t_color a, t_color b)
{
	a.r = ft_min((uint64_t)a.r + b.r, 255);
	a.g = ft_min((uint64_t)a.g + b.g, 255);
	a.b = ft_min((uint64_t)a.b + b.b, 255);
	return (a);
}

t_color	color_prod(t_color a, t_color b)
{
	a.r = ((uint16_t)a.r * b.r) / 255;
	a.g = ((uint16_t)a.g * b.g) / 255;
	a.b = ((uint16_t)a.b * b.b) / 255;
	return (a);
}

t_color	color_invert(t_color color)
{
	t_color	res;

	res.r = 255 - color.r;
	res.g = 255 - color.g;
	res.b = 255 - color.b;
	return	(res);
}

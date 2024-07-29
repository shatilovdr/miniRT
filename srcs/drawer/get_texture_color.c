/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:30:01 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/29 18:20:22 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_texture_color(t_coord coord, const mlx_image_t *texture)
{
	t_color		res;
	int			x;
	int			y;
	uint8_t		*pixelstart;

	x = (int)(coord.loc_y * texture->width) % texture->width;
	y = (int)((-1.0 * coord.loc_x + 1) * texture->height) % texture->height;
	pixelstart = texture->pixels
		+ (y * texture->width + x) * 4;
	res.r = (*(pixelstart));
	res.g = (*(pixelstart + 1));
	res.b = (*(pixelstart + 2));
	return (res);
}

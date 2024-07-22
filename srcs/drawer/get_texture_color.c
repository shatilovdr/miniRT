/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:30:01 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/22 14:32:16 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_texture_color(t_coord coord, const mlx_image_t *img)
{
	int		x;
	int		y;
	uint8_t	*pixel;
	t_color	color;

	x = ((int)((1 - coord.loc_x) * img->width) + img->width / 2) % img->width;
	y = (int)((1 - coord.loc_y) * img->height) % img->height;
	if (0 <= x && x < (int) img->width && 0 <= y && y < (int) img->height)
	{
		pixel = img->pixels + (y * img->width + x) * sizeof(int32_t);
		color.r = *pixel;
		color.g = *(pixel + 1);
		color.b = *(pixel + 2);
		return (color);
	}
	return ((t_color){0, 0, 0});
}

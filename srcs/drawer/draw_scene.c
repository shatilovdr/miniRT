/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:00:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/22 14:32:01 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_mlx(t_scene *scene);
void	track_esc(mlx_key_data_t keydata, void *param);

int	draw_scene(t_scene *scene)
{
	calculate_img(scene);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	mlx_key_hook(scene->mlx, track_esc, scene->mlx);
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
	return (0);
}

void	track_esc(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *)param);
}

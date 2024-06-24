/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:00:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/24 23:31:56 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_mlx(t_scene *scene);
void	track_esc(mlx_key_data_t keydata, void *param);

int	draw_scene(t_scene *scene)
{
	if (init_mlx(scene))
		return (1);
	calculate_img(scene);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	mlx_key_hook(scene->mlx, track_esc, scene->mlx);
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
	return (0);
}

int	init_mlx(t_scene *sc)
{
	sc->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!sc->mlx)
		return (1);
	sc->img = mlx_new_image(sc->mlx, sc->mlx->width, sc->mlx->height);
	if (!sc->img)
	{
		mlx_terminate(sc->mlx);
		return (1);
	}
	return (0);
}

void	track_esc(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *)param);
}

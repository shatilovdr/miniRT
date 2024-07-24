/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:49:44 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/24 14:01:17 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint8_t	init_mlx(t_scene *sc)
{
	sc->mlx = getmlx();
	if (!sc->mlx)
		return (0);
	sc->img = mlx_new_image(sc->mlx, sc->mlx->width, sc->mlx->height);
	if (!sc->img)
	{
		mlx_terminate(sc->mlx);
		return (0);
	}
	return (1);
}

mlx_t	*getmlx(void)
{
	static mlx_t	*mlx = NULL;

	if (!mlx)
		mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	return (mlx);
}

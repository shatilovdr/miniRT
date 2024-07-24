/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:49:44 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/23 14:50:43 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

mlx_t	*getmlx(void)
{
	static mlx_t	*mlx = NULL;

	if (!mlx)
		mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	return (mlx);
}

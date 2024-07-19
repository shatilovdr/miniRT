/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_closest_hp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:44:38 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/19 12:45:12 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hp	*select_closest_hp(t_hp *a, t_hp *b)
{
	if (a->type == OBJ_NONE)
		return (b);
	if (b->type == OBJ_NONE)
		return (a);
	if (a->dist < b->dist)
		return (a);
	else
		return (b);
}

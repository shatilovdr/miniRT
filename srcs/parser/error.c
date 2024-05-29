/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:57:28 by ivalimak          #+#    #+#             */
/*   Updated: 2024/05/27 20:49:00 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "ft_stdio/ft_printf.h"

int32_t	rt_perror(void)
{
	const int32_t	err = errno;
	const char		*msg;

	msg = ft_push(ft_strlower(ft_strdup(strerror(err))));
	if (!msg || !*msg)
		msg = strerror(err);
	ft_dprintf(2, "miniRT: %s\n", msg);
	return (err);
}

int32_t	rt_ferror(const char *err)
{
	ft_dprintf(2, "Error\n");
	ft_dprintf(2, "%s\n", err);
	return (1);
}

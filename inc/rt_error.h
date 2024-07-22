/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:56:30 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/22 16:37:22 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERROR_H
# define RT_ERROR_H
# include <errno.h>
# include <stdint.h>
# include <string.h>

// error.c
int32_t	rt_perror(void);
int32_t	rt_ferror(const char *err);

#endif

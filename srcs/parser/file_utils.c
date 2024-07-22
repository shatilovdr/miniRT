/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:47:09 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/22 16:52:19 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

static inline int32_t	*_scenefile(void);

int32_t	openscene(const char *path)
{
	int32_t	*scene;

	scene = _scenefile();
	if (*scene == SCENE_CLOSED)
		*scene = open(path, O_RDONLY);
	return (*scene);
}

int32_t	getscene(void)
{
	return (*_scenefile());
}

void	closescene(void)
{
	int32_t	*scene;

	scene = _scenefile();
	if (*scene >= 0)
	{
		close(*scene);
		*scene = SCENE_CLOSED;
	}
}

static inline int32_t	*_scenefile(void)
{
	static int32_t	scene = SCENE_CLOSED;

	return (&scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:56:40 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/24 16:15:15 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_scene	*_getscene(const char *path);

int32_t	main(int32_t argc, char **argv)
{
	t_scene	*scene;

	if (argc == 2)
		scene = _getscene(argv[1]);
	else
	{
		ft_dprintf(2, "miniRT: usage: miniRT [scene file]\n");
		return (ft_return(1));
	}
	if (!scene->amb || !scene->lights || !scene->cam)
	{
		if (!scene->amb)
			ft_dprintf(2, "miniRT: no ambient light found in scene file\n");
		if (!scene->lights)
			ft_dprintf(2, "miniRT: no light found in scene file\n");
		if (!scene->cam)
			ft_dprintf(2, "miniRT: no camera found in scene file\n");
		rt_exit(1);
	}
	draw_scene(scene);
	rt_exit(0);
}

void	rt_exit(const int32_t estat)
{
	closescene();
	mlx_terminate(getmlx());
	ft_exit(estat);
}

static inline t_scene	*_getscene(const char *path)
{
	uint64_t	fnamelen;
	const char	*basename;

	basename = ft_strrchr(path, '/');
	if (basename)
		basename++;
	else
		basename = path;
	fnamelen = ft_strlen(basename);
	if (fnamelen < 4 || !ft_strequals(basename + fnamelen - 3, ".rt"))
		ft_exit(rt_ferror("Invalid file format"));
	return (parsefile(path));
}

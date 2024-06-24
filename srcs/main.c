/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:56:40 by dshatilo          #+#    #+#             */
/*   Updated: 2024/06/24 21:30:19 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_stdio/ft_printf.h"

static inline t_scene	*_getscene(const char *path);
// static inline void		_dbg_pscene(t_scene *scene);

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
	if (!scene->light || !scene->cam)
	{
		if (!scene->light)
			ft_dprintf(2, "miniRT: no light found in scene file\n");
		if (!scene->cam)
			ft_dprintf(2, "miniRT: no camera found in scene file\n");
		return (ft_return(1));
	}
	// _dbg_pscene(scene);
	return (ft_return(0));
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

// #include <stdio.h>

// static inline void		_dbg_pscene(t_scene *scene)
// {
// 	const t_cylinder	*cyl;
// 	const t_sphere		*sph;
// 	const t_plane		*pln;

// 	if (scene->amb)
// 	{
// 		printf("Ambient Light:\n");
// 		printf("\t%20s %Lf\n", "ratio:", scene->amb->ratio);
// 		printf("\t%20s ", "color:");
// 		printf("%u,%u,%u\n\n", scene->amb->color.r, scene->amb->color.g, scene->amb->color.b);
// 	}
// 	else
// 		printf("No Ambient Light\n\n");
// 	if (scene->cam)
// 	{
// 		printf("Camera:\n");
// 		printf("\t%20s ", "pos:");
// 		printf("%Lf,%Lf,%Lf\n", scene->cam->pos.x, scene->cam->pos.y, scene->cam->pos.z);
// 		printf("\t%20s ", "orientation:");
// 		printf("%Lf,%Lf,%Lf\n", scene->cam->orientation.x, scene->cam->orientation.y, scene->cam->orientation.z);
// 		printf("\t%20s %u\n\n", "fov:", scene->cam->fov);
// 	}
// 	else
// 		printf("No Camera\n\n");
// 	if (scene->light)
// 	{
// 		printf("Light:\n");
// 		printf("\t%20s ", "pos:");
// 		printf("%Lf,%Lf,%Lf\n", scene->light->pos.x, scene->light->pos.y, scene->light->pos.z);
// 		printf("\t%20s %Lf\n", "brightness:", scene->light->brightness);
// 		printf("\t%20s ", "color:");
// 		printf("%u,%u,%u\n\n", scene->light->color.r, scene->light->color.g, scene->light->color.b);
// 	}
// 	else
// 		printf("No Light\n\n");
// 	if (!scene->spheres)
// 		printf("No Spheres\n\n");
// 	else while (scene->spheres)
// 	{
// 		sph = scene->spheres->blk;
// 		printf("Sphere:\n");
// 		printf("\t%20s ", "pos:");
// 		printf("%Lf,%Lf,%Lf\n", sph->pos.x, sph->pos.y, sph->pos.z);
// 		printf("\t%20s %Lf\n", "diameter:", sph->diameter);
// 		printf("\t%20s ", "color:");
// 		printf("%u,%u,%u\n\n", sph->color.r, sph->color.g, sph->color.b);
// 		scene->spheres = scene->spheres->next;
// 	}
// 	if (!scene->planes)
// 		printf("No Planes\n\n");
// 	else while (scene->planes)
// 	{
// 		pln = scene->planes->blk;
// 		printf("Plane:\n");
// 		printf("\t%20s ", "pos:");
// 		printf("%Lf,%Lf,%Lf\n", pln->pos.x, pln->pos.y, pln->pos.z);
// 		printf("\t%20s ", "normal:");
// 		printf("%Lf,%Lf,%Lf\n", pln->normal.x, pln->normal.y, pln->normal.z);
// 		printf("\t%20s ", "color:");
// 		printf("%u,%u,%u\n\n", pln->color.r, pln->color.g, pln->color.b);
// 		scene->planes = scene->planes->next;
// 	}
// 	if (!scene->cylinders)
// 		printf("No Cylinders\n");
// 	else while (scene->cylinders)
// 	{
// 		cyl = scene->cylinders->blk;
// 		printf("Cylinder:\n");
// 		printf("\t%20s ", "pos:");
// 		printf("%Lf,%Lf,%Lf\n", cyl->pos.x, cyl->pos.y, cyl->pos.z);
// 		printf("\t%20s ", "normal:");
// 		printf("%Lf,%Lf,%Lf\n", cyl->axis.x, cyl->axis.y, cyl->axis.z);
// 		printf("\t%20s %Lf\n", "diameter:", cyl->diameter);
// 		printf("\t%20s %Lf\n", "height:", cyl->height);
// 		printf("\t%20s ", "color:");
// 		printf("%u,%u,%u\n", cyl->color.r, cyl->color.g, cyl->color.b);
// 		scene->cylinders = scene->cylinders->next;
// 		if (scene->cylinders)
// 			printf("\n");
// 	}
// }

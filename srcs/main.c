/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:56:40 by dshatilo          #+#    #+#             */
/*   Updated: 2024/07/19 18:24:36 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio/ft_printf.h"
#include "minirt.h"

// static inline t_scene	*_getscene(const char *path);
// static inline void		_dbg_pscene(t_scene *scene);

// int32_t	main(int32_t argc, char **argv)
// {
// 	t_scene	*scene;

// 	if (argc == 2)
// 		scene = _getscene(argv[1]);
// 	else
// 	{
// 		ft_dprintf(2, "miniRT: usage: miniRT [scene file]\n");
// 		return (ft_return(1));
// 	}
// 	if (!scene->light || !scene->cam)
// 	{
// 		if (!scene->light)
// 			ft_dprintf(2, "miniRT: no light found in scene file\n");
// 		if (!scene->cam)
// 			ft_dprintf(2, "miniRT: no camera found in scene file\n");
// 		return (ft_return(1));
// 	}
// 	draw_scene(scene);
// 	// _dbg_pscene(scene);
// 	return (ft_return(0));
// }

// static inline t_scene	*_getscene(const char *path)
// {
// 	uint64_t	fnamelen;
// 	const char	*basename;

// 	basename = ft_strrchr(path, '/');
// 	if (basename)
// 		basename++;
// 	else
// 		basename = path;
// 	fnamelen = ft_strlen(basename);
// 	if (fnamelen < 4 || !ft_strequals(basename + fnamelen - 3, ".rt"))
// 		ft_exit(rt_ferror("Invalid file format"));
// 	return (parsefile(path));
// }

// // #include <stdio.h>

// // static inline void		_dbg_pscene(t_scene *scene)
// // {
// // 	const t_conic	*cyl;
// // 	const t_sphere		*sph;
// // 	const t_plane		*pln;

// // 	if (scene->amb)
// // 	{
// // 		printf("Ambient Light:\n");
// // 		printf("\t%20s %Lf\n", "ratio:", scene->amb->ratio);
// // 		printf("\t%20s ", "color:");
// // 		printf("%u,%u,%u\n\n", scene->amb->color.r, scene->amb->color.g,
// scene->amb->color.b);
// // 	}
// // 	else
// // 		printf("No Ambient Light\n\n");
// // 	if (scene->cam)
// // 	{
// // 		printf("Camera:\n");
// // 		printf("\t%20s ", "pos:");
// // 		printf("%Lf,%Lf,%Lf\n", scene->cam->pos.x, scene->cam->pos.y,
// scene->cam->pos.z);
// // 		printf("\t%20s ", "orientation:");
// // 		printf("%Lf,%Lf,%Lf\n", scene->cam->orientation.x,
// scene->cam->orientation.y, scene->cam->orientation.z);
// // 		printf("\t%20s %u\n\n", "fov:", scene->cam->fov);
// // 	}
// // 	else
// // 		printf("No Camera\n\n");
// // 	if (scene->light)
// // 	{
// // 		printf("Light:\n");
// // 		printf("\t%20s ", "pos:");
// // 		printf("%Lf,%Lf,%Lf\n", scene->light->pos.x, scene->light->pos.y,
// scene->light->pos.z);
// // 		printf("\t%20s %Lf\n", "brightness:", scene->light->brightness);
// // 		printf("\t%20s ", "color:");
// // 		printf("%u,%u,%u\n\n", scene->light->color.r, scene->light->color.g,
// scene->light->color.b);
// // 	}
// // 	else
// // 		printf("No Light\n\n");
// // 	if (!scene->spheres)
// // 		printf("No Spheres\n\n");
// // 	else while (scene->spheres)
// // 	{
// // 		sph = scene->spheres->blk;
// // 		printf("Sphere:\n");
// // 		printf("\t%20s ", "pos:");
// // 		printf("%Lf,%Lf,%Lf\n", sph->pos.x, sph->pos.y, sph->pos.z);
// // 		printf("\t%20s %Lf\n", "diameter:", sph->diameter);
// // 		printf("\t%20s ", "color:");
// // 		printf("%u,%u,%u\n\n", sph->color.r, sph->color.g, sph->color.b);
// // 		scene->spheres = scene->spheres->next;
// // 	}
// // 	if (!scene->planes)
// // 		printf("No Planes\n\n");
// // 	else while (scene->planes)
// // 	{
// // 		pln = scene->planes->blk;
// // 		printf("Plane:\n");
// // 		printf("\t%20s ", "pos:");
// // 		printf("%Lf,%Lf,%Lf\n", pln->pos.x, pln->pos.y, pln->pos.z);
// // 		printf("\t%20s ", "normal:");
// // 		printf("%Lf,%Lf,%Lf\n", pln->normal.x, pln->normal.y, pln->normal.z);
// // 		printf("\t%20s ", "color:");
// // 		printf("%u,%u,%u\n\n", pln->color.r, pln->color.g, pln->color.b);
// // 		scene->planes = scene->planes->next;
// // 	}
// // 	if (!scene->cylinders)
// // 		printf("No Cylinders\n");
// // 	else while (scene->cylinders)
// // 	{
// // 		cyl = scene->cylinders->blk;
// // 		printf("Cylinder:\n");
// // 		printf("\t%20s ", "pos:");
// // 		printf("%Lf,%Lf,%Lf\n", cyl->pos.x, cyl->pos.y, cyl->pos.z);
// // 		printf("\t%20s ", "normal:");
// // 		printf("%Lf,%Lf,%Lf\n", cyl->axis.x, cyl->axis.y, cyl->axis.z);
// // 		printf("\t%20s %Lf\n", "diameter:", cyl->diameter);
// // 		printf("\t%20s %Lf\n", "height:", cyl->height);
// // 		printf("\t%20s ", "color:");
// // 		printf("%u,%u,%u\n", cyl->color.r, cyl->color.g, cyl->color.b);
// // 		scene->cylinders = scene->cylinders->next;
// // 		if (scene->cylinders)
// // 			printf("\n");
// // 	}
// // }


int32_t main(void)
{
	t_light		light		= {(t_vec3){5, 5, 0}, 0.5, (t_color){255, 255, 255}};
	t_list		lights		= {&light, NULL, NULL, NULL};
	t_amb_light	alight		= {0.3, (t_color){255, 255, 255}};
	t_camera	camera		= {(t_vec3){0, 0, -10}, (t_vec3){0, 0, 1}, 100};

	t_sphere	sphere		= {(t_vec3){-2,0,0}, 3.0f, (t_color){0, 255, 0}};
	t_sphere	sphere2		= {(t_vec3){1,0,0}, 1.0f, (t_color){255, 0, 0}};
	t_list		spheres2	= {&sphere2, NULL, NULL, NULL};
	t_list		spheres		= {&sphere, NULL, &spheres2, NULL};

	t_plane		plane		= {(t_vec3){1,0,0}, (t_vec3){0, 1, 0}, (t_color){0, 255, 0}};
	t_list		planes		= {&plane, NULL, NULL, NULL};

	t_vec3		axis ={4, 2, 0};
	t_conic	cylinder	= {(t_vec3){3,3,2}, vec3_unit(axis), 2, 4, (t_color){255, 0, 0}};
	t_conic	cylinder2	= {(t_vec3){-1,0,2}, vec3_unit(axis), 2, 4, (t_color){0, 0, 255}};
	t_conic	cylinder3	= {(t_vec3){-3,-3,2}, vec3_unit(axis), 2, 4, (t_color){0, 255, 0}};
	t_list		cylinders3	= {&cylinder3, NULL, NULL, NULL};
	t_list		cylinders2	= {&cylinder2, NULL, &cylinders3, NULL};
	t_list		cylinders	= {&cylinder, NULL, &cylinders2, NULL};

	t_vec3		axis1 ={-4, 2, 0};
	t_conic	cone	= {(t_vec3){3,3,2}, vec3_unit(axis1), 2, 4, (t_color){100, 30, 0}};
	t_conic	cone2	= {(t_vec3){-1,0,2}, vec3_unit(axis1), 2, 4, (t_color){0, 200, 255}};
	t_conic	cone3	= {(t_vec3){-3,-3,2}, vec3_unit(axis1), 2, 4, (t_color){255, 0, 255}};
	t_list		cones3	= {&cone3, NULL, NULL, NULL};
	t_list		cones2	= {&cone2, NULL, &cones3, NULL};
	t_list		cones	= {&cone, NULL, &cones2, NULL};

	// t_scene		scene = {0, &alight, &camera, &lights, NULL, NULL, NULL, &cones, NULL, NULL};		
	t_scene		scene = {0, &alight, &camera, &lights, &cylinders, &spheres, &planes, &cones, NULL, NULL};


	draw_scene(&scene);
	return (ft_return(0));
}

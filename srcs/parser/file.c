/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:51:32 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/23 16:55:43 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline uint8_t	_checktype(t_scene *scene, const char *line);
static inline uint8_t	_getobj(t_scene *scene, const char *line, uint8_t type);
static inline uint8_t	_addobj(const t_list **list, const void *obj);
static inline uint8_t	_init_mlx(t_scene *sc);

t_scene	*parsefile(const char *path)
{
	char	*line;
	t_scene		*out;
	size_t		i;

	out = ft_push(ft_calloc(1, sizeof(*out)));
	if (!out || !_init_mlx(out))
		ft_exit(rt_perror());
	if (openscene(path) == -1)
		ft_exit(rt_perror());
	line = ft_push(ft_strtrim(get_next_line(getscene()), "\t\n\v\f\r "));
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (ft_strchr("\t\n\v\f\r", line[i]))
				line[i] = ' ';
			i++;
		}
		if (!_checktype(out, line))
			rt_exit(rt_ferror("Unrecognized element"));
		ft_popblk(line);
		line = ft_push(ft_strtrim(get_next_line(getscene()), "\t\n\v\f\r "));
	}
	closescene();
	return (out);
}

static inline uint8_t	_checktype(t_scene *scene, const char *line)
{
	if (*line == 'A' && !scene->amb)
	{
		scene->amb = parse_alight(line);
		return (scene->amb != NULL);
	}
	if (*line == 'C' && !scene->cam)
	{
		scene->cam = parse_camera(line);
		return (scene->cam != NULL);
	}
	if (*line == 'L')
		return (_getobj(scene, line, OBJ_LGT));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (_getobj(scene, line, OBJ_SPH));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (_getobj(scene, line, OBJ_PLN));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (_getobj(scene, line, OBJ_CON));
	if (*line == 'A' || *line == 'C' || *line == 'L')
		ft_exit(rt_ferror("Duplicate element found"));
	return (*line == '\0' || *line == '#');
}

static inline uint8_t	_getobj(t_scene *scene, const char *line, uint8_t type)
{
	const t_list	**list;
	const void		*obj;

	obj = NULL;
	if (type == OBJ_LGT)
	{
		obj = parse_light(line);
		list = &scene->lights;
	}
	if (type == OBJ_SPH)
	{
		obj = parse_sph(line);
		list = &scene->spheres;
	}
	else if (type == OBJ_PLN)
	{
		obj = parse_pln(line);
		list = &scene->planes;
	}
	else if (type == OBJ_CON)
	{
		obj = parse_con(line);
		list = &scene->cylinders;
	}
	return (_addobj(list, obj));
}

static inline uint8_t	_addobj(const t_list **list, const void *obj)
{
	const t_list	*node;

	if (!obj)
		return (0);
	node = ft_lstnew(obj);
	if (!node)
	{
		rt_perror();
		return (0);
	}
	ft_lstadd_back(list, (t_list *)node);
	return (*list != NULL);
}

static inline uint8_t	_init_mlx(t_scene *sc)
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

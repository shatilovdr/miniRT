/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:51:32 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/22 16:58:12 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

static inline uint8_t	_checktype(t_scene *scene, const char *line);
static inline uint8_t	_getobj(t_scene *scene, const char *line, uint8_t type);
static inline uint8_t	_addobj(const t_list **list, const void *obj);

t_scene	*parsefile(const char *path)
{
	const char	*line;
	t_scene		*out;

	out = ft_push(ft_calloc(1, sizeof(*out)));
	if (!out)
		ft_exit(rt_perror());
	if (openscene(path) == -1)
		ft_exit(rt_perror());
	line = ft_push(ft_strtrim(get_next_line(getscene()), "\t\n\v\f\r "));
	while (line)
	{
		if (!_checktype(out, line))
			rt_exit(rt_ferror("Unrecognized element"));
		ft_popblk(line);
		line = ft_push(ft_strtrim(get_next_line(getscene()), "\t\n\v\f\r "));
	}
	closescene();
	return (out);
}

void	rt_exit(const int32_t estat)
{
	closescene();
	ft_exit(estat);
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
	if (*line == 'L' && !scene->light)
	{
		scene->light = parse_light(line);
		return (scene->light != NULL);
	}
	if (ft_strncmp(line, "sp", 2) == 0)
		return (_getobj(scene, line, OBJ_SPH));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (_getobj(scene, line, OBJ_PLN));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (_getobj(scene, line, OBJ_CYL));
	if (*line == 'A' || *line == 'C' || *line == 'L')
		ft_exit(rt_ferror("Duplicate element found"));
	return (*line == '\0' || *line == '#');
}

static inline uint8_t	_getobj(t_scene *scene, const char *line, uint8_t type)
{
	const t_list	**list;
	const void		*obj;

	obj = NULL;
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
	else if (type == OBJ_CYL)
	{
		obj = parse_cyl(line);
		list = &scene->cylinders;
	}
	if (!obj)
		return (0);
	return (_addobj(list, obj));
}

static inline uint8_t	_addobj(const t_list **list, const void *obj)
{
	const t_list	*node;

	node = ft_lstnew(obj);
	if (!node)
	{
		rt_perror();
		return (0);
	}
	ft_lstadd_back(list, (t_list *)node);
	return (*list != NULL);
}

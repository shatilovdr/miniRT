/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:51:32 by ivalimak          #+#    #+#             */
/*   Updated: 2024/07/24 16:47:00 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline uint8_t	_checktype(t_scene *scene, const char *line);
static inline uint8_t	_getobj(t_scene *scene, const char *line, uint8_t type);
static inline uint8_t	_addobj(const t_list **list, const void *obj);
static inline t_list	**_getlist(const t_scene *scene, const uint8_t type);

t_scene	*parsefile(const char *path)
{
	char	*line;
	t_scene	*out;
	size_t	i;

	out = ft_push(ft_calloc(1, sizeof(*out)));
	if (!out || !init_mlx(out) || openscene(path) == -1)
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
		return (_getobj(scene, line, OBJ_CYL));
	if (ft_strncmp(line, "co", 2) == 0)
		return (_getobj(scene, line, OBJ_CON));
	if (*line == 'A' || *line == 'C')
		ft_exit(rt_ferror("Duplicate element found"));
	return (*line == '\0' || *line == '#');
}

static inline uint8_t	_getobj(t_scene *scene, const char *line, uint8_t type)
{
	const void		*obj;

	obj = NULL;
	if (type == OBJ_LGT)
		obj = parse_light(line);
	else if (type == OBJ_SPH)
		obj = parse_sph(line);
	else if (type == OBJ_PLN)
		obj = parse_pln(line);
	else if (type == OBJ_CYL || type == OBJ_CON)
		obj = parse_con(line);
	return (_addobj((const t_list **)_getlist(scene, type), obj));
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

static inline t_list	**_getlist(const t_scene *scene, const uint8_t type)
{
	if (type == OBJ_LGT)
		return ((t_list **)&scene->lights);
	if (type == OBJ_SPH)
		return ((t_list **)&scene->spheres);
	if (type == OBJ_PLN)
		return ((t_list **)&scene->planes);
	if (type == OBJ_CYL)
		return ((t_list **)&scene->cylinders);
	if (type == OBJ_CON)
		return ((t_list **)&scene->cones);
	return (NULL);
}

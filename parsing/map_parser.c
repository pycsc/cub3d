/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    map_parser.c                                          +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 21:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 21:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * is_map_line - Checks if a line is part of the map.
 * @line: The line to check.
 *
 * Return: 1 if it is a map line, 0 otherwise.
 */
int	is_map_line(char *line)
{
	int	i;

	if (!line || *line == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && \
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && \
			line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	add_map_line(char *line, t_data *data)
{
	t_list	*new;
	char	*content;

	content = ft_strdup(line);
	if (!content)
		return (1);
	if (content[ft_strlen(content) - 1] == '\n')
		content[ft_strlen(content) - 1] = '\0';
	new = ft_lstnew(content);
	if (!new)
	{
		free(content);
		return (1);
	}
	ft_lstadd_back(&data->map_list, new);
	return (0);
}

int	lst_to_array(t_data *data)
{
	int		size;
	int		i;
	t_list	*tmp;

	size = ft_lstsize(data->map_list);
	data->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map)
		return (1);
	tmp = data->map_list;
	i = 0;
	while (tmp)
	{
		data->map[i] = (char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

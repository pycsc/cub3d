/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    parser_utils.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 19:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:46:19 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_config_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2) || \
		!ft_strncmp(line + i, "WE", 2) || !ft_strncmp(line + i, "EA", 2) || \
		!ft_strncmp(line + i, "F", 1) || !ft_strncmp(line + i, "C", 1))
		return (1);
	return (0);
}

static int	parse_rgb(char **tab)
{
	int	rgb[3];
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && (tab[i][j] == ' ' || (tab[i][j] >= 9 && tab[i][j] <= 13)))
			j++;
		if (!tab[i][j])
			return (-1);
		while (tab[i][j] && ft_isdigit(tab[i][j]))
			j++;
		while (tab[i][j] && (tab[i][j] == ' ' || (tab[i][j] >= 9 && tab[i][j] <= 13)))
			j++;
		if (tab[i][j] != '\0' && tab[i][j] != '\n')
			return (-1);
		rgb[i] = ft_atoi(tab[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (-1);
		i++;
	}
	return ((i != 3) ? -1 : (rgb[0] << 16 | rgb[1] << 8 | rgb[2]));
}

static int	set_color(int *col, char *line)
{
	char	**tab;
	int		val;

	if (*col != -1)
		return (print_error("Duplicate color definition"), 1);
	tab = ft_split(line + 1, ',');
	if (!tab)
		return (print_error("Memory allocation failed"), 1);
	val = parse_rgb(tab);
	free_tab(tab);
	if (val == -1)
		return (print_error("Invalid color format (must be R,G,B [0-255])"), 1);
	*col = val;
	return (0);
}

static int	set_tex(char **tex, char *line)
{
	int		i;
	int		start;

	if (*tex)
		return (print_error("Duplicate texture definition"), 1);
	i = 2;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (!line[i] || line[i] == '\n')
		return (print_error("Missing texture path"), 1);
	start = i;
	while (line[i] && line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13) && line[i] != '\n')
		i++;
	*tex = ft_substr(line, start, i - start);
	if (!*tex)
		return (print_error("Memory allocation failed"), 1);
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] && line[i] != '\n')
		return (free(*tex), *tex = NULL, print_error("Extra characters after texture path"), 1);
	return (0);
}

int	parse_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (!ft_strncmp(line + i, "NO", 2) && (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
		return (set_tex(&data->config.no_tex, line + i));
	if (!ft_strncmp(line + i, "SO", 2) && (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
		return (set_tex(&data->config.so_tex, line + i));
	if (!ft_strncmp(line + i, "WE", 2) && (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
		return (set_tex(&data->config.we_tex, line + i));
	if (!ft_strncmp(line + i, "EA", 2) && (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
		return (set_tex(&data->config.ea_tex, line + i));
	if (!ft_strncmp(line + i, "F", 1) && (line[i + 1] == ' ' || (line[i + 1] >= 9 && line[i + 1] <= 13)))
		return (set_color(&data->config.floor_col, line + i));
	if (!ft_strncmp(line + i, "C", 1) && (line[i + 1] == ' ' || (line[i + 1] >= 9 && line[i + 1] <= 13)))
		return (set_color(&data->config.ceiling_col, line + i));
	return (0);
}

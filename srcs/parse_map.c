#include "fdf.h"

static int	size_line(char **line)
{
	int	size;

	size = 0;
	while (line[size] != NULL)
		size++;
	return (size);
}

int	parse_map(t_map *map, char *path)
{
	char	**line;
	t_list	*lst;
	t_list	*tmp;
	int		x;
	int		y;

	lst = file_to_lst(path);
	map->height = ft_lstsize(lst);
	map->width = 0;
	map->map = malloc(map->height * sizeof(int *));
	y = 0;
	while (lst)
	{
		line = ft_split(lst->content, ' ');
		if (map->width == 0)
			map->width = size_line(line);
		map->map[y] = malloc(size_line(line) * sizeof(int));
		x = 0;
		while (line[x] != NULL)
		{
			map->map[y][x] = ft_atoi(line[x]);
			free(line[x]);
			x++;
		}
		y++;
		tmp = lst;
		lst = lst->next;
		ft_lstdelone(tmp, &free);
		free(line);
	}
	return (0);
}

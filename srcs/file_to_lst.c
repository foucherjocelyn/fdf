#include "fdf.h"

t_list	*file_to_lst(char *path)
{
	int		fd;
	t_list	*lst;
	char	*line;

	lst = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&lst, ft_lstnew(line));
	free(line);
	return (lst);
}

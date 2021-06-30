#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"

typedef struct	s_map
{
	int	**map;
	int	width;
	int	height;
}				t_map;

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_fdf
{
	t_mlx	mlx;
	t_data	data;
	t_map	map;
}				t_fdf;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *img, int x1, int y1, int x2, int y2);
t_list	*file_to_lst(char *path);
int		parse_map(t_map *map, char *path);

#endif

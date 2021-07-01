#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"
#define WIN_WIDTH 1200
#define WIN_HEIGHT 600

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct	s_map
{
	int	**map;
	int	width;
	int	height;
}				t_map;

typedef struct	s_iso
{
	t_point	**map;
	int		width;
	int		height;
	int		x_offset;
	int		y_offset;
	int		tile_width;
	int		tile_height;
}				t_iso;

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
	t_iso	iso;
}				t_fdf;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *img, int x1, int y1, int x2, int y2);
t_list	*file_to_lst(char *path);
int		parse_map(t_map *map, char *path);
void	map_to_iso(t_map map, t_iso *iso);
void	draw_map(t_fdf *fdf);
void	draw_pixel(t_fdf *fdf, int x, int y, int color);

#endif

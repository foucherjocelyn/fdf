#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	key_hook(int keycode, t_mlx *mlx)
{
	(void)mlx;
	printf("%d\n", keycode);
	if (keycode == 65307)
		exit(0);
	return (0);
}

t_data	img;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	my_mlx_pixel_put(&img, x, y, color);
	mlx_put_image_to_window(mlx->ptr, mlx->win, img.img, 0, 0);
}

void	draw_line_low(int x1, int y1, int x2, int y2)
{
	int dx;
	int	dy;
	int	yi;
	int	e;

	dx = x2 - x1;
	dy = y2 - y1;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	e = 2 * dy - dx;
	while (x1 < x2)
	{
		my_mlx_pixel_put(&img, x1, y1, 0x00FF00);
		if (e > 0)
		{
			y1 += yi;
			e += 2 * (dy - dx);
		}
		else
			e += 2 * dy;
		x1++;
	}
}

void	draw_line_high(int x1, int y1, int x2, int y2)
{
	int dx;
	int	dy;
	int	xi;
	int	e;

	dx = x2 - x1;
	dy = y2 - y1;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	e = 2 * dx - dy;
	while (y1 < y2)
	{
		my_mlx_pixel_put(&img, x1, y1, 0x00FF00);
		if (e > 0)
		{
			x1 += xi;
			e += 2 * (dx - dy);
		}
		else
			e += 2 * dx;
		y1++;
	}
}

void	draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2)
{
	if (abs(y2 - y1) < abs(x2 - x1))
	{
		if (x1 > x2)
			draw_line_low(x2, y2, x1, y1);
		else
			draw_line_low(x1, y1, x2, y2);
	}
	else
	{
		if (y1 > y2)
			draw_line_high(x2, y2, x1, y1);
		else
			draw_line_high(x1, y1, x2, y2);
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, img.img, 0, 0);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	static int	x1 = 0;
	static int	y1 = 0;

	printf("button %d, x %d y %d\n", button, x, y);
	if (button == 1)
	{
		if (x1 == 0 || y1 == 0)
		{
			x1 = x;
			y1 = y;
		}
		else
		{
			draw_line(mlx, x1, y1, x, y);
			x1 = 0;
			y1 = 0;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	(void)argc;
	(void)argv;
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, 800, 600, "fdf");
	img.img = mlx_new_image(mlx.ptr, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_loop(mlx.ptr);
	return (0);
}

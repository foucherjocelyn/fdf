#include "fdf.h"
#include "libft.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	(void)mlx;
	printf("%d\n", keycode);
	if (keycode == 65307)
		exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	my_mlx_pixel_put(&(fdf->data), x, y, color);
	mlx_put_image_to_window(fdf->mlx.ptr, fdf->mlx.win, fdf->data.img, 0, 0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
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
			draw_line(&fdf->data, x1, y1, x, y);
			x1 = 0;
			y1 = 0;
			mlx_put_image_to_window(fdf->mlx.ptr, fdf->mlx.win,
				fdf->data.img, 0, 0);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2)
	{
		parse_map(&(fdf.map), argv[1]);
		fdf.mlx.ptr = mlx_init();
		fdf.mlx.win = mlx_new_window(fdf.mlx.ptr, 800, 600, "fdf");
		fdf.data.img = mlx_new_image(fdf.mlx.ptr, 800, 600);
		fdf.data.addr = mlx_get_data_addr(fdf.data.img, &(fdf.data.bits_per_pixel), &(fdf.data.line_length), &(fdf.data.endian));
		mlx_key_hook(fdf.mlx.win, key_hook, &(fdf.mlx));
		mlx_mouse_hook(fdf.mlx.win, mouse_hook, &fdf);
		mlx_loop(fdf.mlx.ptr);
	}
	return (0);
}

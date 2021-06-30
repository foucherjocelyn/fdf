#include "fdf.h"

static int	ft_abs(int value)
{
	if (value < 0)
		value = -value;
	return (value);
}

static void	draw_line_low(t_data *img, int x1, int y1, int x2, int y2)
{
	int	dx;
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
		my_mlx_pixel_put(img, x1, y1, 0x00FF00);
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

static void	draw_line_high(t_data *img, int x1, int y1, int x2, int y2)
{
	int	dx;
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
		my_mlx_pixel_put(img, x1, y1, 0x00FF00);
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

void	draw_line(t_data *img, int x1, int y1, int x2, int y2)
{
	if (ft_abs(y2 - y1) < ft_abs(x2 - x1))
	{
		if (x1 > x2)
			draw_line_low(img, x2, y2, x1, y1);
		else
			draw_line_low(img, x1, y1, x2, y2);
	}
	else
	{
		if (y1 > y2)
			draw_line_high(img, x2, y2, x1, y1);
		else
			draw_line_high(img, x1, y1, x2, y2);
	}
}

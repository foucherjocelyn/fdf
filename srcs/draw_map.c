#include "fdf.h"

void	draw_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->iso.height)
	{
		j = 0;
		while (j < fdf->iso.width)
		{
			if (fdf->iso.map[i][j].x < WIN_WIDTH && fdf->iso.map[i][j].y < WIN_HEIGHT)
				draw_pixel(fdf, fdf->iso.map[i][j].x, fdf->iso.map[i][j].y, 0x00FF00);
			if (i < fdf->iso.height - 1)
				draw_line(&fdf->data, fdf->iso.map[i][j].x, fdf->iso.map[i][j].y, fdf->iso.map[i+1][j].x, fdf->iso.map[i+1][j].y);
			if (j < fdf->iso.width - 1)
				draw_line(&fdf->data, fdf->iso.map[i][j].x, fdf->iso.map[i][j].y, fdf->iso.map[i][j+1].x, fdf->iso.map[i][j+1].y);
			printf("%d %d\n", fdf->iso.map[i][j].x, fdf->iso.map[i][j].y);
			j++;
		}
		i++;
	}
}

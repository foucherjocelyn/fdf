#include "fdf.h"

static void	init_map_to_iso(t_map map, t_iso *iso)
{
	iso->width = map.width;
	iso->height = map.height;
	iso->y_offset = 20;
	iso->x_offset = WIN_WIDTH / 2;
	iso->tile_width = WIN_WIDTH / iso->width / 2;
	iso->tile_height = WIN_HEIGHT / iso->height / 2;
	iso->map = malloc(sizeof(t_point *) * map.height);
}

void	map_to_iso(t_map map, t_iso *iso)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	i = 0;
	init_map_to_iso(map, iso);
	while (i < map.height)
	{
		iso->map[i] = malloc(sizeof(t_point) * map.width);
		j = 0;
		while (j < map.width)
		{
			screen_x = j * iso->tile_width;
			screen_y = i * iso->tile_height;
			iso->map[i][j].x = ((screen_x - screen_y) * cos(0.523599)) + iso->x_offset;
			iso->map[i][j].y = (- (map.map[i][j] * 2) + ((screen_y + screen_x) * sin(0.523599))) + iso->y_offset;
			j++;
		}
		i++;
	}
}

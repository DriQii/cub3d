#include <cub3d.h>

void	ft_create_minimap(t_data *data)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	while (data->map[index.i])
	{
		while (data->map[index.i][index.j])
		{
			if (data->map[index.i][index.j] == '1')
				my_4x4_pixel_put(&data->frame, index.j * 4, index.i * 4,
					0x000000FF);
			else if (data->map[index.i][index.j] == '0'
				|| data->map[index.i][index.j] == 'N'
				|| data->map[index.i][index.j] == 'S'
				|| data->map[index.i][index.j] == 'W'
				|| data->map[index.i][index.j] == 'E')
				my_4x4_pixel_put(&data->frame, index.j * 4, index.i * 4,
					0x0000FF00);
			index.j++;
		}
		index.j = 0;
		index.i++;
	}
	my_player_pixel_put(&data->frame, data->player.x * 4, data->player.y * 4,
		0x00FF0000);
}

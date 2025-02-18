#include <cub3d.h>

int ft_print_minimap(t_data *data)
{
	t_index	index;

	index.i = 0;
	index.j = 0;

	ft_moove_pos(data);
	data->player.dx = cos(data->player.angle);
	data->player.dy = sin(data->player.angle);
	while(data->map[index.i])
	{
		while(data->map[index.i][index.j])
		{
			if(data->map[index.i][index.j] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->wall.img, index.j * 4, index.i * 4);
			if(data->map[index.i][index.j] == '0' || data->map[index.i][index.j] == 'N')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->floor.img, index.j * 4, index.i * 4);
			index.j++;
		}
		index.j = 0;
		index.i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->player.img, data->player.x * (float)4, data->player.y * (float)4);
	ft_put_fov(data);
	return (0);
}

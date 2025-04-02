#include <cub3d.h>

void	ft_init(t_data *data)
{
	int x;
	int y;
	t_index index;

	data->wall.img = mlx_xpm_file_to_image(data->mlx, "./img/wall.xpm", &x, &y);
	data->wall.addr = mlx_get_data_addr(data->wall.img, &data->wall.bits_per_pixel, &data->wall.line_length, &data->wall.endian);


	index.i = 0;
	index.j = 0;
	while (data->map[index.i])
	{
		index.j = 0;
		while (data->map[index.i][index.j])
		{
			if (data->map[index.i][index.j] == 'S')
			{
				data->player.pa = M_PI_2;
				data->player.x = index.j;
				data->player.y = index.i;
			}
			if (data->map[index.i][index.j] == 'W')
			{
				data->player.pa = M_PI;
				data->player.x = index.j;
				data->player.y = index.i;
			}
			if (data->map[index.i][index.j] == 'N')
			{
				data->player.pa = M_PI + M_PI_2;
				data->player.x = index.j;
				data->player.y = index.i;
			}
			if (data->map[index.i][index.j] == 'E')
			{
				data->player.pa = 0;
				data->player.x = index.j;
				data->player.y = index.i;
			}
			index.j++;
		}
		index.i++;
	}
	data->keyState[W] = 0;
	data->keyState[A] = 0;
	data->keyState[S] = 0;
	data->keyState[D] = 0;
	data->keyState[L] = 0;
	data->keyState[R] = 0;
	data->mouse.x = 0;
	data->mouse.y = 0;
	data->player.speed = 0.1;
}

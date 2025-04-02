#include <cub3d.h>

void	ft_create_frame(t_data *data)
{
	data->frame.img = mlx_new_image(data->mlx, 1080, 720);
	data->frame.addr = mlx_get_data_addr(data->frame.img, &data->frame.bits_per_pixel, &data->frame.line_length, &data->frame.endian);
	ft_create_minimap(data);
}

int	ft_render(t_data *data)
{
	ft_moove_pos(data);
	ft_moove_fov(data);
	ft_create_frame(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->frame.img, 0, 0);
	mlx_destroy_image(data->mlx, data->frame.img);

	return (0);
}
void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_4x4_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	t_index	index;

	index.x = 0;
	index.y = 0;
	while(index.x < 4)
	{
		while(index.y < 4)
		{
			dst = data->addr + ((y + index.y) * data->line_length + (x + index.x) * (data->bits_per_pixel / 8));
			*(unsigned int*)dst = color;
			index.y++;
		}
		index.y = 0;
		index.x++;
	}
}

void	my_player_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	t_index	index;

	index.x = -1;
	index.y = -1;
	while(index.x < 2)
	{
		while(index.y < 2)
		{
			dst = data->addr + ((y + index.y) * data->line_length + (x + index.x) * (data->bits_per_pixel / 8));
			*(unsigned int*)dst = color;
			index.y++;
		}
		index.y = -1;
		index.x++;
	}
}

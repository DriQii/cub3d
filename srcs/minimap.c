#include <cub3d.h>


float ft_find_distance(float x, float y, float nX, float nY)
{
	float dist;
	float dx = nX - x;
	float dy = nY - y;
	dist = sqrt(dy*dy + dx*dx);
	return (dist);
}

t_pos ft_find_wall(t_data *data, float angle)
{
	t_pos	pos;
	int		i;

	i = 0;
	pos.x = data->player.x;
	pos.y = data->player.y;

	while(data->map[(int)pos.y][(int)pos.x] != '1')
	{
		if (i < 5)
		{
			my_pixel_put(&data->frame, pos.x * 4, pos.y * 4, 0x00000000);
			i++;
		}
		pos.x += cos(angle);
		pos.y += sin(angle);
	}
	pos.x -= cos(angle);
	pos.y -= sin(angle);
	while(data->map[(int)pos.y][(int)pos.x] != '1')
	{
		pos.x += cos(angle) * 0.01;
		pos.y += sin(angle) * 0.01;
	}
	return (pos);
}

void ft_put_bg(t_data *data, int x)
{
	t_index	index;

	index.i = 0;
	while(index.i < WIN_LENGHT)
	{
		if (index.i < WIN_LENGHT / 2)
			my_pixel_put(&data->frame, x, index.i, 0x0000F0FF);
		else
			my_pixel_put(&data->frame, x, index.i, 0x00FFF0F0);
		index.i++;
	}
}

void ft_put_line(t_data *data, float dist, int x, float angle)
{
	int i;
	int j;
	dist *= cos(angle - data->player.pa);
	ft_put_bg(data, x);
	int	wallLen = WIN_LENGHT / dist / 2;
	if (wallLen < WIN_LENGHT)
		i = (WIN_LENGHT - wallLen) / 2;
	else
		i = 0;
	j = 0;
	//printf("i = %d x = %d walllen = %d\n", i, x, wallLen);
	while(j < wallLen && i < WIN_LENGHT)
	{
		j++;
		my_pixel_put(&data->frame, x, i, 0x0000FF00);
		i++;
	}
	//printf("%d\n", wallLen);

}



void	ft_show_fov(t_data *data)
{
	t_index	index;
	t_pos pos;
	float	angle;
	float	decalage;

	index.i = 0;
	angle = data->player.pa - 0.525;
	decalage = 1.05 / WIN_WIDTH;
	while(index.i < 1080)
	{
		pos = ft_find_wall(data, angle);
		ft_put_line(data, ft_find_distance(data->player.x, data->player.y, pos.x, pos.y), index.i, angle);
		angle += decalage;
		index.i++;
	}
}
void	ft_create_minimap(t_data *data)
{
	ft_show_fov(data);
	t_index index;
	index.i = 0;
	index.j = 0;
	while(data->map[index.i])
	{
		while(data->map[index.i][index.j])
		{
			if (data->map[index.i][index.j] == '1')
				my_4x4_pixel_put(&data->frame, index.j * 4, index.i * 4, 0x000000FF);
			else if (data->map[index.i][index.j] == '0')
				my_4x4_pixel_put(&data->frame, index.j * 4, index.i * 4, 0x0000FF00);
			index.j++;
		}
		index.j = 0;
		index.i++;
	}
	my_player_pixel_put(&data->frame, data->player.x * 4, data->player.y * 4, 0x00FF0000);
}


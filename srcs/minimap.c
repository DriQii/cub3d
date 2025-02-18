#include <cub3d.h>


void	ft_print_array(t_data *data, float dx, float dy)
{
	float	array;

	array = 1;
	while (data->map[(int)(data->player.y + (dy * array))][(int)(data->player.x + (dx * array))] != '1')
	{
		//printf("%d, %d, %c\n", (int)(data->player.y + (dy * array)), (int)(data->player.x + (dx * array)), data->map[(int)(data->player.y + (data->player.dy * array))][(int)(data->player.x + (data->player.dx* array))]);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->delta.img, (data->player.x + (dx * array)) * (float)4, (data->player.y + (dy * array)) * (float)4);
		array += 0.1;
	}
}

//ft_print_()
void	ft_put_fov(t_data *data)
{
	float	array;
	float	angle;
	float	dx;
	float	dy;
	float total;

	angle = 0;

	ft_print_array(data, data->player.dx, data->player.dy);
	while (angle < M_PI_4)
	{
		angle += 0.12;
		total = data->player.angle + angle;
		if (total > M_PI * 2)
			total -= M_PI * 2;
		else if (total < 0)
			total += M_PI * 2;
		//printf("total : %f %f\n", total, data->player.angle);
		dx = cos(total);
		dy = sin(total);
		ft_print_array(data, dx, dy);
		//mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->delta.img, (data->player.x + (dx * array)) * (float)4, (data->player.y + (dy * array)) * (float)4);
	}
	angle = 0;
	while (angle < M_PI_4)
	{
		angle += 0.1;
		total = data->player.angle - angle;
		if (total > M_PI * 2)
			total -= M_PI * 2;
		else if (total < 0)
			total += M_PI * 2;
		//printf("total : %f\n", total);
		dx = cos(total);
		dy = sin(total);
		ft_print_array(data, dx, dy);
		//mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->delta.img, (data->player.x + (dx * array)) * (float)4, (data->player.y + (dy * array)) * (float)4);
	}


}

void	ft_modify_angle(char c, t_data *data)
{
	if (c == '-')
		data->player.angle -= 0.1;
	else if (c == '+')
		data->player.angle += 0.1;
	if (data->player.angle > M_PI * 2)
		data->player.angle -= M_PI * 2;
	else if (data->player.angle < 0)
		data->player.angle += M_PI * 2;

}

void	ft_moove_pos(t_data *data)
{
	if (data->keystate[W] == 1)
	{
		data->player.y += data->player.dy / 5;
		data->player.x += data->player.dx / 5;
	}
	else if (data->keystate[A] == 1)
		ft_modify_angle('-', data);
	else if (data->keystate[S] == 1)
	{
		data->player.y -= data->player.dy / 5;
		data->player.x -= data->player.dx / 5;
	}
	else if (data->keystate[D] == 1)
		ft_modify_angle('+', data);
}

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

/* ft_render(t_data *data)
{
	data->minimap.
	img = mlx_new_image(data->mlx, WIN_WIDTH , 1080);

} */

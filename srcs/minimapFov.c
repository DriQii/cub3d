#include <cub3d.h>

static void	ft_print_array(t_data *data, float total)
{
	float	array;
	float	dx = cos(total);
	float	dy = sin(total);
	array = 1;
	while (data->map[(int)(data->player.y + (dy * array))][(int)(data->player.x + (dx * array))] != '1')
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->delta.img, (data->player.x + (dx * array)) * (float)4, (data->player.y + (dy * array)) * (float)4);
		array += 0.1;
	}
}
static void	ft_print_fov_angle(float angle, t_data *data, char c)
{
	float total;

	total = 0;
	if (c == '+')
		total = data->player.angle + angle;
	else if (c == '-')
		total = data->player.angle - angle;
	if (total > M_PI * 2)
		total -= M_PI * 2;
	else if (total < 0)
		total += M_PI * 2;
	ft_print_array(data, total);
}
void	ft_put_fov(t_data *data)
{
	float	angle;

	angle = 0;

	ft_print_array(data, data->player.angle);
	while (angle < M_PI_4)
	{
		angle += 0.1;
		ft_print_fov_angle(angle, data, '+');
	}
	angle = 0;
	while (angle < M_PI_4)
	{
		angle += 0.1;
		ft_print_fov_angle(angle, data, '-');
	}
}

static void	ft_modify_angle(char c, t_data *data)
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

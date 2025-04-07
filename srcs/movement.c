#include <cub3d.h>

static void calculate_delta(float *dx, float *dy, float pa)
{
	*dx += cos(pa);
	*dy += sin(pa);
}

void	ft_moove_pos(t_data *data)
{
	float dx = 0;
	float dy = 0;
	if(data->keyState[W] == 1)
		calculate_delta(&dx, &dy, data->player.pa);
	if(data->keyState[S] == 1)
		calculate_delta(&dx, &dy, data->player.pa + M_PI);
	if(data->keyState[A] == 1)
		calculate_delta(&dx, &dy, data->player.pa - M_PI_2);
	if(data->keyState[D] == 1)
		calculate_delta(&dx, &dy, data->player.pa + M_PI_2);
	if (data->map[(int)(data->player.y + dy * (data->player.speed))][(int)(data->player.x + dx * data->player.speed)] != '1')
	{
		data->player.x += dx * data->player.speed;
		data->player.y += dy * data->player.speed;
	}
}

void	ft_moove_fov(t_data *data)
{
	if(data->keyState[L] == 1)
		data->player.pa -= 0.05;
	if(data->keyState[R] == 1)
		data->player.pa += 0.05;
	if(data->player.pa > M_PI * 2)
		data->player.pa -= M_PI * 2;
	else if(data->player.pa < 0)
		data->player.pa += M_PI * 2;

}

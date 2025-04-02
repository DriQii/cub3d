#include <cub3d.h>


void ft_print_fov_minimap(t_data *data, float angle)
{
	t_pos	pos;
	int		i;

	i = 0;
	pos.x = data->player.x;
	pos.y = data->player.y;

	while(data->map[(int)pos.y][(int)pos.x] && data->map[(int)pos.y][(int)pos.x] != '1')
	{
		if (i < 4)
		{
			my_pixel_put(&data->frame, pos.x * 4, pos.y * 4, 0x00000000);
			i++;
		}
		pos.x += cos(angle);
		pos.y += sin(angle);
	}
}
void ft_init_side_dist(t_data *data, t_ray *ray, float angle)
{
	ray->rayDirX = cos(angle);
	ray->rayDirY = sin(angle);
	ray->deltaX = (ray->rayDirX == 0) ? 1e30 : fabs(1 / ray->rayDirX);
	ray->deltaY = (ray->rayDirY == 0) ? 1e30 : fabs(1 / ray->rayDirY);
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->player.x - ray->mapX) * ray->deltaX;
	}
	else if (ray->rayDirX >= 0)
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1 - data->player.x) * ray->deltaX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->player.y - ray->mapY) * ray->deltaY;
	}
	else if (ray->rayDirY >= 0)
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1 - data->player.y) * ray->deltaY;
	}
}

void ft_dda_loop(t_data *data, t_ray *ray)
{
	int		hit;

	hit = 0;

	while(!hit)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaX;
			ray->mapX += ray->stepX;
			ray->finalDir = 'x';
		}
		else
		{
			ray->sideDistY += ray->deltaY;
			ray->mapY += ray->stepY;
			ray->finalDir = 'y';
		}

		if (data->map[ray->mapY][ray->mapX] == '1')
			hit = 1;
	}
}

float ft_find_wall(t_data *data, float angle)
{
	t_ray	ray;


	ray.mapX = (int)data->player.x;
	ray.mapY = (int)data->player.y;
	ft_init_side_dist(data, &ray, angle);
	ft_dda_loop(data, &ray);
	if (ray.finalDir == 'x')
		ray.finalDist = ray.sideDistX - ray.deltaX;
	else
		ray.finalDist = ray.sideDistY - ray.deltaY;
	return (ray.finalDist);
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
	while(j < wallLen && i < WIN_LENGHT)
	{
		j++;
		my_pixel_put(&data->frame, x, i, 0x0000FF00);
		i++;
	}
}


void	ft_show_minimap_fov(t_data *data)
{
	t_index	index;
	float	angle;
	float	decalage;

	index.i = 0;
	angle = data->player.pa - 0.525;
	decalage = 1.05 /( WIN_WIDTH / 2);
	while(index.i < WIN_WIDTH / 2)
	{
		ft_print_fov_minimap(data, angle);
		angle += decalage;
		index.i++;
	}
}
void	ft_show_fov(t_data *data)
{
	t_index	index;
	float	dist;
	float	angle;
	float	decalage;

	index.i = 0;
	angle = data->player.pa - 0.525;
	decalage = 1.05 / WIN_WIDTH;
	while(index.i < 1080)
	{
		dist = ft_find_wall(data, angle);
		ft_put_line(data, dist, index.i, angle);
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
	ft_show_minimap_fov(data);
	my_player_pixel_put(&data->frame, data->player.x * 4, data->player.y * 4, 0x00FF0000);
}


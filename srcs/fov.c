#include <cub3d.h>

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
void	ft_print_wall(t_data *data, int x, int i, t_ray ray)
{

	int		texX;
	int		offset;

	texX = (ray.impact * WALL_WIDHT);
	offset = (ray.texY * data->wall.line_length) + (texX * (data->wall.bits_per_pixel / 8));
	my_pixel_put(&data->frame, x, i, *(unsigned int *)(data->wall.addr + offset));
}



void ft_put_line(t_data *data, t_ray *ray, int x, float angle)
{
	t_index index;
	float		txPos;

	ft_set_index(data, ray, &index, angle);
	ft_print_bg(data, x, ray->wallLen);
	ray->impact = ft_find_impact(*ray, data, angle);
	ray->wStart = -ray->wallLen / 2 + WIN_LENGHT / 2;
	txPos = 0;
	if (ray->wStart < 0)
	{
		ray->wStart *= -1;
		txPos = ray->wStart * ray->step;
	}
	while(index.j < ray->wallLen && index.i < WIN_LENGHT)
	{
		index.j++;
		ft_print_wall(data, x, index.i, *ray);
		index.i++;
		txPos+= ray->step;
		ray->texY = txPos;
	}
}
void	ft_create_fov(t_data *data)
{
	t_index	index;
	t_ray	ray;
	float	angle;
	float	decalage;



	index.i = 0;
	angle = data->player.pa - FOVRAD / 2;
	decalage = FOVRAD / WIN_WIDTH;
	while(index.i < WIN_WIDTH)
	{
		ray = ft_find_dist(data, angle);
		ft_put_line(data, &ray, index.i, angle);
		angle += decalage;
		index.i++;
	}
}

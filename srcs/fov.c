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
void	ft_set_step(t_data *data, t_ray *ray)
{
	if(ray->finalDir == 'x' && ray->stepX == -1)
	{
		ray->texX = (ray->impact * data->weTex.width);
		ray->step = (float)data->weTex.height / ray->wallLen;
	}
	else if(ray->finalDir == 'x' && ray->stepX == 1)
	{
		ray->texX = (ray->impact * data->eaTex.width);
		ray->step = (float)data->eaTex.height / ray->wallLen;
	}
	else if(ray->finalDir == 'y' && ray->stepY == -1)
	{
		ray->texX = (ray->impact * data->noTex.width);
		ray->step = (float)data->noTex.height / ray->wallLen;
	}
	else if(ray->finalDir == 'y' && ray->stepY == 1)
	{
		ray->texX = (ray->impact * data->soTex.width);
		ray->step = (float)data->soTex.height / ray->wallLen;
	}
}

void	ft_print_wall(t_data *data, int x, int i, t_ray ray)
{
	int		offset;
	if(ray.finalDir == 'x' && ray.stepX == -1)
	{
		offset = (ray.texY * data->weTex.line_length) + ((data->weTex.width - 1 - ray.texX) * (data->weTex.bits_per_pixel / 8));
		my_pixel_put(&data->frame, x, i, *(unsigned int *)(data->weTex.addr + offset));
	}
	else if(ray.finalDir == 'x' && ray.stepX == 1)
	{
		offset = (ray.texY * data->eaTex.line_length) + (ray.texX * (data->eaTex.bits_per_pixel / 8));
		my_pixel_put(&data->frame, x, i, *(unsigned int *)(data->eaTex.addr + offset));
	}
	else if(ray.finalDir == 'y' && ray.stepY == -1)
	{
		offset = (ray.texY * data->noTex.line_length) + (ray.texX * (data->noTex.bits_per_pixel / 8));
		my_pixel_put(&data->frame, x, i, *(unsigned int *)(data->noTex.addr + offset));
	}
	else if(ray.finalDir == 'y' && ray.stepY == 1)
	{
		offset = (ray.texY * data->soTex.line_length) + ((data->soTex.width - 1 - ray.texX) * (data->soTex.bits_per_pixel / 8));
		my_pixel_put(&data->frame, x, i, *(unsigned int *)(data->soTex.addr + offset));
	}
}



void ft_put_line(t_data *data, t_ray *ray, int x, float angle)
{
	t_index index;
	float		txPos;

	ft_set_index(data, ray, &index, angle);
	ft_print_bg(data, x, ray->wallLen);
	ray->impact = ft_find_impact(*ray, data, angle);
	ft_set_step(data, ray);
	ray->wStart = -ray->wallLen / 2 + WIN_LENGHT / 2;
	txPos = 0;
	if (ray->wStart < 0)
	{
		txPos = (-ray->wStart) * ray->step;
		ray->wStart = 0;
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

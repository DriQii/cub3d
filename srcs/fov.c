#include <cub3d.h>

static void ft_init_side_dist(t_data *data, t_ray *ray, float angle)
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

static void ft_dda_loop(t_data *data, t_ray *ray)
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

static t_ray	ft_find_dist(t_data *data, float angle)
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
	return (ray);
}
float	ft_find_impact(t_ray ray, t_data *data, float angle)
{
	float	impact;
	float	posImpact;

	if (ray.finalDir == 'x')
	{
		posImpact = data->player.y + ray.finalDist * sin(angle);
		impact = posImpact - floor(posImpact);
	}
	else
	{
		posImpact = data->player.x + ray.finalDist * cos(angle);
		impact = posImpact - floor(posImpact);
	}
	return (impact);
}
void	ft_print_wall(t_data *data, int x, int i, t_ray ray)
{

	int		texX;
	int		offset;

	texX = (ray.impact * WALL_WIDHT);
	offset = (ray.texY * data->wall.line_length) + (texX * (data->wall.bits_per_pixel / 8));
	my_pixel_put(&data->frame, x, i, *(unsigned int *)(data->wall.addr + offset));
}

void	ft_print_bg(t_data *data, int x, int wallen)
{
	int	i;

	i = 0;
	while(i < WIN_LENGHT)
	{
		if (i < (WIN_LENGHT - wallen) / 2)
			my_pixel_put(&data->frame, x, i, 0x0000F0FF);
		else if (i > (WIN_LENGHT - wallen) / 2 + wallen)
			my_pixel_put(&data->frame, x, i, 0x00FFF0F0);
		i++;
	}
}

void ft_put_line(t_data *data, t_ray ray, int x, float angle)
{
	t_index index;
	float	step;
	float		txPos;

	index.i = 0;
	index.j = 0;
	ray.finalDist *= cos(angle - data->player.pa);
	int	wallLen = WIN_LENGHT / ray.finalDist / 2;
	if (wallLen < WIN_LENGHT)
		index.i = (WIN_LENGHT - wallLen) / 2;
	else
		index.i = 0;
	index.j = 0;
	step = (float)WALL_HEIGHT / wallLen;
	txPos = 0;
	ray.texY = 0;
	ft_print_bg(data, x, wallLen);
	ray.impact = ft_find_impact(ray, data, angle);
	while(index.j < wallLen && index.i < WIN_LENGHT)
	{
		index.j++;
		ft_print_wall(data, x, index.i, ray);
		index.i++;
		txPos+= step;
		ray.texY = txPos;
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
		ft_put_line(data, ray, index.i, angle);
		angle += decalage;
		index.i++;
	}
}

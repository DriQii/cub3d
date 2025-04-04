#include <cub3d.h>

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

t_ray	ft_find_dist(t_data *data, float angle)
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
void ft_set_index(t_data *data, t_ray *ray, t_index *index, float angle)
{
	index->i = 0;
	index->j = 0;
	ray->finalDist *= cos(angle - data->player.pa);
	ray->wallLen = WIN_LENGHT / ray->finalDist;
	if (ray->wallLen < WIN_LENGHT)
		index->i = (WIN_LENGHT - ray->wallLen) / 2;
	else
		index->i = 0;
	index->j = 0;
	ray->step = (float)WALL_HEIGHT / ray->wallLen;
	ray->texY = 0;
}

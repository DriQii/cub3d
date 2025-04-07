/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fovUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:25 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 00:49:54 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_print_bg(t_data *data, int x, int wallen)
{
	int	i;

	i = 0;
	while (i < WIN_LENGHT)
	{
		if (i < (WIN_LENGHT - wallen) / 2)
			my_pixel_put(&data->frame, x, i, data->fColor);
		else if (i > (WIN_LENGHT - wallen) / 2 + wallen)
			my_pixel_put(&data->frame, x, i, data->cColor);
		i++;
	}
}

t_ray	ft_find_dist(t_data *data, float angle)
{
	t_ray	ray;

	ray.mapX = (int)data->player.x;
	ray.mapY = (int)data->player.y;
	ray.rayDirX = cos(angle);
	ray.rayDirY = sin(angle);
	if (ray.rayDirX == 0)
		ray.deltaX = 1e30;
	else
		ray.deltaX = fabs(1 / ray.rayDirX);
	if (ray.rayDirY == 0)
		ray.deltaY = 1e30;
	else
		ray.deltaY = fabs(1 / ray.rayDirY);
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
	float	pos_impact;

	if (ray.finalDir == 'x')
	{
		pos_impact = data->player.y + ray.finalDist * ray.rayDirY;
		impact = pos_impact - floor(pos_impact);
	}
	else
	{
		pos_impact = data->player.x + ray.finalDist * ray.rayDirX;
		impact = pos_impact - floor(pos_impact);
	}
	return (impact);
}

void	ft_set_index(t_data *data, t_ray *ray, t_index *index, float angle)
{
	index->i = 0;
	index->j = 0;
	ray->wallLen = WIN_LENGHT / (ray->finalDist * cos(angle - data->player.pa));
	if (ray->wallLen < WIN_LENGHT)
		index->i = (WIN_LENGHT - ray->wallLen) / 2;
	else
		index->i = 0;
	index->j = 0;
	ray->texY = 0;
}

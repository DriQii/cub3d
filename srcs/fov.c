/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:23 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 00:48:37 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_init_side_dist(t_data *data, t_ray *ray, float angle)
{
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

void	ft_dda_loop(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
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
	if (ray->finalDir == 'x' && ray->stepX == -1)
	{
		ray->texX = (ray->impact * data->weTex.width);
		ray->step = (float)data->weTex.height / ray->wallLen;
	}
	else if (ray->finalDir == 'x' && ray->stepX == 1)
	{
		ray->texX = (ray->impact * data->eaTex.width);
		ray->step = (float)data->eaTex.height / ray->wallLen;
	}
	else if (ray->finalDir == 'y' && ray->stepY == -1)
	{
		ray->texX = (ray->impact * data->noTex.width);
		ray->step = (float)data->noTex.height / ray->wallLen;
	}
	else if (ray->finalDir == 'y' && ray->stepY == 1)
	{
		ray->texX = (ray->impact * data->soTex.width);
		ray->step = (float)data->soTex.height / ray->wallLen;
	}
}

int	ft_print_one_wall(t_img *img, t_index index, t_ray ray, t_img *frame)
{
	int	offset;

	if ((ray.finalDir == 'x' && ray.stepX == -1)
		|| (ray.finalDir == 'y' && ray.stepY == 1))
	{
		offset = (ray.texY * img->line_length) + ((img->width - 1
					- ray.texX) * (img->bits_per_pixel / 8));
	}
	else
	{
		offset = (ray.texY * img->line_length) + (ray.texX
				* (img->bits_per_pixel / 8));
	}
	my_pixel_put(frame, index.x, index.i, *(unsigned int *)(img->addr
			+ offset));
	return (offset);
}

void	ft_print_wall(t_data *data, int x, int i, t_ray ray)
{
	t_index	index;

	index.x = x;
	index.i = i;
	if (ray.finalDir == 'x' && ray.stepX == -1)
		ft_print_one_wall(&data->weTex, index, ray, &data->frame);
	else if (ray.finalDir == 'x' && ray.stepX == 1)
		ft_print_one_wall(&data->eaTex, index, ray, &data->frame);
	else if (ray.finalDir == 'y' && ray.stepY == -1)
		ft_print_one_wall(&data->noTex, index, ray, &data->frame);
	else if (ray.finalDir == 'y' && ray.stepY == 1)
		ft_print_one_wall(&data->soTex, index, ray, &data->frame);
}

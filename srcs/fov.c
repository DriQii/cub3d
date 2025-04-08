/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:23 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 09:03:25 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_init_side_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) * ray->delta_x;
	}
	else if (ray->ray_dir_x >= 0)
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - data->player.x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_y;
	}
	else if (ray->ray_dir_y >= 0)
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - data->player.y) * ray->delta_y;
	}
}

void	ft_dda_loop(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->final_dir = 'x';
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->final_dir = 'y';
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	ft_set_step(t_data *data, t_ray *ray)
{
	if (ray->final_dir == 'x' && ray->step_x == -1)
	{
		ray->tex_x = (ray->impact * data->we_tex.width);
		ray->step = (float)data->we_tex.height / ray->wall_len;
	}
	else if (ray->final_dir == 'x' && ray->step_x == 1)
	{
		ray->tex_x = (ray->impact * data->ea_tex.width);
		ray->step = (float)data->ea_tex.height / ray->wall_len;
	}
	else if (ray->final_dir == 'y' && ray->step_y == -1)
	{
		ray->tex_x = (ray->impact * data->no_tex.width);
		ray->step = (float)data->no_tex.height / ray->wall_len;
	}
	else if (ray->final_dir == 'y' && ray->step_y == 1)
	{
		ray->tex_x = (ray->impact * data->so_tex.width);
		ray->step = (float)data->so_tex.height / ray->wall_len;
	}
}

int	ft_print_one_wall(t_img *img, t_index index, t_ray ray, t_img *frame)
{
	int	offset;

	if ((ray.final_dir == 'x' && ray.step_x == -1)
		|| (ray.final_dir == 'y' && ray.step_y == 1))
	{
		offset = (ray.tex_y * img->line_length) + ((img->width - 1
					- ray.tex_x) * (img->bits_per_pixel / 8));
	}
	else
	{
		offset = (ray.tex_y * img->line_length) + (ray.tex_x
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
	if (ray.final_dir == 'x' && ray.step_x == -1)
		ft_print_one_wall(&data->we_tex, index, ray, &data->frame);
	else if (ray.final_dir == 'x' && ray.step_x == 1)
		ft_print_one_wall(&data->ea_tex, index, ray, &data->frame);
	else if (ray.final_dir == 'y' && ray.step_y == -1)
		ft_print_one_wall(&data->no_tex, index, ray, &data->frame);
	else if (ray.final_dir == 'y' && ray.step_y == 1)
		ft_print_one_wall(&data->so_tex, index, ray, &data->frame);
}

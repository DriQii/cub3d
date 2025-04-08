/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fovUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:25 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 09:04:00 by evella           ###   ########.fr       */
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
			my_pixel_put(&data->frame, x, i, data->f_color);
		else if (i > (WIN_LENGHT - wallen) / 2 + wallen)
			my_pixel_put(&data->frame, x, i, data->c_color);
		i++;
	}
}

t_ray	ft_find_dist(t_data *data, float angle)
{
	t_ray	ray;

	ray.map_x = (int)data->player.x;
	ray.map_y = (int)data->player.y;
	ray.ray_dir_x = cos(angle);
	ray.ray_dir_y = sin(angle);
	if (ray.ray_dir_x == 0)
		ray.delta_x = 1e30;
	else
		ray.delta_x = fabs(1 / ray.ray_dir_x);
	if (ray.ray_dir_y == 0)
		ray.delta_y = 1e30;
	else
		ray.delta_y = fabs(1 / ray.ray_dir_y);
	ft_init_side_dist(data, &ray);
	ft_dda_loop(data, &ray);
	if (ray.final_dir == 'x')
		ray.final_dist = ray.side_dist_x - ray.delta_x;
	else
		ray.final_dist = ray.side_dist_y - ray.delta_y;
	return (ray);
}

float	ft_find_impact(t_ray ray, t_data *data)
{
	float	impact;
	float	pos_impact;

	if (ray.final_dir == 'x')
	{
		pos_impact = data->player.y + ray.final_dist * ray.ray_dir_y;
		impact = pos_impact - floor(pos_impact);
	}
	else
	{
		pos_impact = data->player.x + ray.final_dist * ray.ray_dir_x;
		impact = pos_impact - floor(pos_impact);
	}
	return (impact);
}

void	ft_set_index(t_data *data, t_ray *ray, t_index *index, float angle)
{
	index->i = 0;
	index->j = 0;
	ray->wall_len = WIN_LENGHT
		/ (ray->final_dist * cos(angle - data->player.pa));
	if (ray->wall_len < WIN_LENGHT)
		index->i = (WIN_LENGHT - ray->wall_len) / 2;
	else
		index->i = 0;
	index->j = 0;
	ray->tex_y = 0;
}

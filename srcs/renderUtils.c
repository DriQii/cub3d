/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:46:55 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 08:59:34 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_4x4_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	t_index	index;

	index.x = 0;
	index.y = 0;
	while (index.x < 4)
	{
		while (index.y < 4)
		{
			dst = data->addr + ((y + index.y) * data->line_length + (x
						+ index.x) * (data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			index.y++;
		}
		index.y = 0;
		index.x++;
	}
}

void	my_player_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	t_index	index;

	index.x = -1;
	index.y = -1;
	while (index.x < 2)
	{
		while (index.y < 2)
		{
			dst = data->addr + ((y + index.y) * data->line_length + (x
						+ index.x) * (data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			index.y++;
		}
		index.y = -1;
		index.x++;
	}
}

void	ft_put_line(t_data *data, t_ray *ray, int x, float angle)
{
	t_index	index;
	float	tx_pos;

	ft_set_index(data, ray, &index, angle);
	ft_print_bg(data, x, ray->wall_len);
	ray->impact = ft_find_impact(*ray, data);
	ft_set_step(data, ray);
	ray->wall_start = -ray->wall_len / 2 + WIN_LENGHT / 2;
	tx_pos = 0;
	if (ray->wall_start < 0)
	{
		tx_pos = (-ray->wall_start) * ray->step;
		ray->wall_start = 0;
	}
	while (index.j < ray->wall_len && index.i < WIN_LENGHT)
	{
		index.j++;
		ft_print_wall(data, x, index.i, *ray);
		index.i++;
		tx_pos += ray->step;
		ray->tex_y = tx_pos;
	}
}

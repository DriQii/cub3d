/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:42 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 00:46:44 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_create_frame(t_data *data)
{
	data->frame.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_LENGHT);
	data->frame.addr = mlx_get_data_addr(data->frame.img,
			&data->frame.bits_per_pixel, &data->frame.line_length,
			&data->frame.endian);
	ft_create_fov(data);
	ft_create_minimap(data);
}

int	ft_render(t_data *data)
{
	ft_moove_pos(data);
	ft_moove_fov(data);
	ft_create_frame(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->frame.img, 0, 0);
	mlx_destroy_image(data->mlx, data->frame.img);
	return (0);
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
	while (index.i < WIN_WIDTH)
	{
		ray = ft_find_dist(data, angle);
		ft_put_line(data, &ray, index.i, angle);
		angle += decalage;
		index.i++;
	}
}

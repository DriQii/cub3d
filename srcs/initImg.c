/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initImg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:27 by evella            #+#    #+#             */
/*   Updated: 2025/02/18 13:46:05 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_init_pos(t_data *data)
{
	t_index	index;

	index.i = 0;
	index.j = 0;

	data->player.angle = 0;
	while(data->map[index.i])
	{
		while(data->map[index.i][index.j])
		{
			if(data->map[index.i][index.j] == 'N')
			{
				data->player.y = index.i;
				data->player.x = index.j;
			}
			index.j++;
		}
		index.j = 0;
		index.i++;
	}
}

void	ft_init_minimap(t_data *data)
{
	int	l;
	int	k;
	data->keystate[W] = 0;
	data->keystate[A] = 0;
	data->keystate[S] = 0;
	data->keystate[D] = 0;
	data->minimap->floor.img = mlx_xpm_file_to_image(data->mlx, "./img/blanc.xpm", &l, &k);
	data->minimap->player.img = mlx_xpm_file_to_image(data->mlx, "./img/rouge.xpm", &l, &k);
	data->minimap->wall.img = mlx_xpm_file_to_image(data->mlx, "./img/bleu.xpm", &l, &k);
	data->minimap->delta.img = mlx_xpm_file_to_image(data->mlx, "./img/noir.xpm", &l, &k);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:01:33 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 09:03:08 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_init_angle(t_data *data, t_index *index)
{
	index->s = 1;
	while (data->map[index->i] && index->s)
	{
		index->j = 0;
		while (data->map[index->i][index->j] && index->s)
		{
			if (data->map[index->i][index->j] == 'S')
				data->player.pa = M_PI_2;
			if (data->map[index->i][index->j] == 'W')
				data->player.pa = M_PI;
			if (data->map[index->i][index->j] == 'N')
				data->player.pa = M_PI + M_PI_2;
			if (data->map[index->i][index->j] == 'E')
				data->player.pa = 0;
			if (data->map[index->i][index->j] == 'S'
				|| data->map[index->i][index->j] == 'W'
				|| data->map[index->i][index->j] == 'N'
				|| data->map[index->i][index->j] == 'E')
				index->s = 0;
			index->j++;
		}
		index->i++;
	}
}

void	ft_set_rgb(t_index *index, t_list *info, t_rgb *rgb)
{
	while (((char *)info->content)[index->j])
	{
		if (((char *)info->content)[index->j] == ',')
		{
			if (index->s == 0)
			{
				rgb->r = atoi(&((char *)info->content)[index->j
						- (index->j - 2)]);
				index->p = index->j + 1;
			}
			else if (index->s == 1)
			{
				rgb->g = atoi(&((char *)info->content)[index->j - (index->j
							- index->p)]);
				rgb->b = atoi(&((char *)info->content)[index->j + 1]);
				break ;
			}
			index->s++;
		}
		index->j++;
	}
}

void	ft_init_color(t_data *data)
{
	t_index	index;
	t_list	*info;
	t_rgb	rgb;

	info = data->info->next->next->next->next;
	index.i = 0;
	index.j = 2;
	index.s = 0;
	while (index.i++ < 2)
	{
		ft_set_rgb(&index, info, &rgb);
		if (index.i == 1)
			data->c_color = (0x00 << 24) | (rgb.r << 16) | (rgb.g << 8) | rgb.b;
		else
			data->f_color = (0x00 << 24) | (rgb.r << 16) | (rgb.g << 8) | rgb.b;
		index.s = 0;
		index.j = 2;
		info = info->next;
	}
}

void	ft_init_var(t_data *data, t_index *index)
{
	data->player.x = index->j - 0.5;
	data->player.y = index->i - 0.5;
	data->key_state[W] = 0;
	data->key_state[A] = 0;
	data->key_state[S] = 0;
	data->key_state[D] = 0;
	data->key_state[L] = 0;
	data->key_state[R] = 0;
	data->player.speed = 0.1;
}

void	ft_init_all(t_data *data)
{
	t_index	index;

	ft_init_tex(data, &index);
	ft_init_angle(data, &index);
	ft_init_var(data, &index);
	ft_init_color(data);
}

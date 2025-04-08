/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:38 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 09:02:53 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	calculate_delta(float *dx, float *dy, float pa)
{
	*dx += cos(pa);
	*dy += sin(pa);
}

void	ft_moove_pos(t_data *data)
{
	float	dx;
	float	dy;

	dx = 0;
	dy = 0;
	if (data->key_state[W] == 1)
		calculate_delta(&dx, &dy, data->player.pa);
	if (data->key_state[S] == 1)
		calculate_delta(&dx, &dy, data->player.pa + M_PI);
	if (data->key_state[A] == 1)
		calculate_delta(&dx, &dy, data->player.pa - M_PI_2);
	if (data->key_state[D] == 1)
		calculate_delta(&dx, &dy, data->player.pa + M_PI_2);
	if (data->map[(int)(data->player.y + dy
			* (data->player.speed))][(int)(data->player.x + dx
			* data->player.speed)] != '1')
	{
		data->player.x += dx * data->player.speed;
		data->player.y += dy * data->player.speed;
	}
}

void	ft_moove_fov(t_data *data)
{
	if (data->key_state[L] == 1)
		data->player.pa -= 0.05;
	if (data->key_state[R] == 1)
		data->player.pa += 0.05;
	if (data->player.pa > M_PI * 2)
		data->player.pa -= M_PI * 2;
	else if (data->player.pa < 0)
		data->player.pa += M_PI * 2;
}

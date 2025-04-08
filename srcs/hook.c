/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:28 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 09:08:07 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_down(int keycode, t_data *data)
{
	if (keycode == WK)
		data->key_state[W] = 1;
	else if (keycode == AK)
		data->key_state[A] = 1;
	else if (keycode == SK)
		data->key_state[S] = 1;
	else if (keycode == DK)
		data->key_state[D] = 1;
	else if (keycode == LK)
		data->key_state[L] = 1;
	else if (keycode == RK)
		data->key_state[R] = 1;
	else if (keycode == ESC)
		close_window(data);
	return (0);
}

int	key_up(int keycode, t_data *data)
{
	if (keycode == WK)
		data->key_state[W] = 0;
	else if (keycode == AK)
		data->key_state[A] = 0;
	else if (keycode == SK)
		data->key_state[S] = 0;
	else if (keycode == DK)
		data->key_state[D] = 0;
	else if (keycode == LK)
		data->key_state[L] = 0;
	else if (keycode == RK)
		data->key_state[R] = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:28 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 09:02:53 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_down(int keycode, t_data *data)
{
	if (keycode == WK)
		data->key_state[W] = 1;
	if (keycode == AK)
		data->key_state[A] = 1;
	if (keycode == SK)
		data->key_state[S] = 1;
	if (keycode == DK)
		data->key_state[D] = 1;
	if (keycode == LK)
		data->key_state[L] = 1;
	if (keycode == RK)
		data->key_state[R] = 1;
	return (0);
}

int	key_up(int keycode, t_data *data)
{
	if (keycode == WK)
		data->key_state[W] = 0;
	if (keycode == AK)
		data->key_state[A] = 0;
	if (keycode == SK)
		data->key_state[S] = 0;
	if (keycode == DK)
		data->key_state[D] = 0;
	if (keycode == LK)
		data->key_state[L] = 0;
	if (keycode == RK)
		data->key_state[R] = 0;
	return (0);
}

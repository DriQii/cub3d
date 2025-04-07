/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:28 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 00:50:44 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_down(int keycode, t_data *data)
{
	if (keycode == WK)
		data->keyState[W] = 1;
	if (keycode == AK)
		data->keyState[A] = 1;
	if (keycode == SK)
		data->keyState[S] = 1;
	if (keycode == DK)
		data->keyState[D] = 1;
	if (keycode == LK)
		data->keyState[L] = 1;
	if (keycode == RK)
		data->keyState[R] = 1;
	return (0);
}

int	key_up(int keycode, t_data *data)
{
	if (keycode == WK)
		data->keyState[W] = 0;
	if (keycode == AK)
		data->keyState[A] = 0;
	if (keycode == SK)
		data->keyState[S] = 0;
	if (keycode == DK)
		data->keyState[D] = 0;
	if (keycode == LK)
		data->keyState[L] = 0;
	if (keycode == RK)
		data->keyState[R] = 0;
	return (0);
}

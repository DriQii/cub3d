/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:25 by evella            #+#    #+#             */
/*   Updated: 2025/04/07 18:26:45 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(*data));
	if (!ft_parsing(argv, data))
		return(1);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_LENGHT, "Cub3D");
	ft_init_all(data);
	mlx_hook(data->mlx_win, 2, 0l, KeyDown, data);
	mlx_hook(data->mlx_win, 3, 0l, KeyUp, data);
	mlx_hook(data->mlx_win, 6, 0l, MouseMoove, data);
	mlx_loop_hook(data->mlx, ft_render, data);
	mlx_loop(data->mlx);
}

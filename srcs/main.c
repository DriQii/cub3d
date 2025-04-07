/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:25 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 01:00:17 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_image(data->mlx, data->noTex.img);
	mlx_destroy_image(data->mlx, data->soTex.img);
	mlx_destroy_image(data->mlx, data->weTex.img);
	mlx_destroy_image(data->mlx, data->eaTex.img);
	ft_freelst(data->info);
	ft_freetabtabb(data->map);
	free(data->mlx);
	free(data);
	exit(0);
	return (0);
}
//mlx_destroy_display(data->mlx);

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (!ft_parsing(argv, data))
		return (1);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_LENGHT, "Cub3D");
	ft_init_all(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_down, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_up, data);
	mlx_hook(data->mlx_win, 17, 0L, close_window, data);
	mlx_loop_hook(data->mlx, ft_render, data);
	mlx_loop(data->mlx);
}

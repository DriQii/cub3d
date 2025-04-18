/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:25 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 09:03:25 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_image(data->mlx, data->no_tex.img);
	mlx_destroy_image(data->mlx, data->so_tex.img);
	mlx_destroy_image(data->mlx, data->we_tex.img);
	mlx_destroy_image(data->mlx, data->ea_tex.img);
	ft_freelst(data->info);
	ft_freetabtabb(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (printf("format : ./cub3d maps/....cub\n"), 1);
	data = malloc(sizeof(*data));
	if (!ft_parsing(argv, data))
		return (free(data), 1);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_LENGHT, "Cub3D");
	ft_init_all(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_down, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_up, data);
	mlx_hook(data->mlx_win, 17, 0L, close_window, data);
	mlx_loop_hook(data->mlx, ft_render, data);
	mlx_loop(data->mlx);
}

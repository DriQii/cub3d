/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:25 by evella            #+#    #+#             */
/*   Updated: 2025/02/18 13:48:06 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_data	data;
	int i = 0;

	ft_parsing(argv, &data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_LENGHT, "Hello world!");
	mlx_do_key_autorepeatoff(data.mlx);
	ft_init_pos(&data);
	ft_init_minimap(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, keyDown, &data);
	mlx_hook(data.mlx_win, 3, 1L<<1, keyUp, &data);
	ft_print_minimap(&data);
	//ft_print_minimap(&data);
	mlx_loop_hook(data.mlx, ft_print_minimap, &data);
	/* while (1)
	{
		if (i == 1000000)
		{
			ft_print_minimap(&data);
			i = 0;
		}
		i++;
	} */
	mlx_loop(data.mlx);
	mlx_do_key_autorepeaton(data.mlx);
}

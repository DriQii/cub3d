/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initImg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:23:30 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 01:02:25 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_init_one_tex(t_data *data, t_img *img, t_list *info)
{
	char	*file;

	file = ft_substr(info->content, 3, ft_strlen(info->content) - 4);
	img->img = mlx_xpm_file_to_image(data->mlx, file, &img->width,
			&img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	free(file);
}

void	ft_init_tex(t_data *data, t_index *index)
{
	t_list	*info;

	index->p = 0;
	index->i = 0;
	index->j = 0;
	info = data->info;
	while (index->p < 4)
	{
		if (((char *)info->content)[0] == 'N')
			ft_init_one_tex(data, &data->noTex, info);
		else if (((char *)info->content)[0] == 'S')
			ft_init_one_tex(data, &data->soTex, info);
		else if (((char *)info->content)[0] == 'W')
			ft_init_one_tex(data, &data->weTex, info);
		else if (((char *)info->content)[0] == 'E')
			ft_init_one_tex(data, &data->eaTex, info);
		index->p++;
		info = info->next;
	}
}

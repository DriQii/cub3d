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

void	ft_init_var(t_data *data, t_index *index)
{
	data->player.x = index->j - 0.5;
	data->player.y = index->i - 0.5;
	data->keyState[W] = 0;
	data->keyState[A] = 0;
	data->keyState[S] = 0;
	data->keyState[D] = 0;
	data->keyState[L] = 0;
	data->keyState[R] = 0;
	data->mouse.x = 0;
	data->mouse.y = 0;
	data->player.speed = 0.1;
}

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

void	ft_init_all(t_data *data)
{
	t_index	index;

	ft_init_tex(data, &index);
	ft_init_angle(data, &index);
	ft_init_var(data, &index);
	ft_init_color(data);
}
void	ft_init_color(t_data *data)
{
	t_index	index;
	t_list	*info;
	int		r;
	int		g;
	int		b;
	int		state;

	info = data->info->next->next->next->next;
	index.i = 0;
	index.j = 2;
	state = 0;
	while (index.i++ < 2)
	{
		while (((char *)info->content)[index.j])
		{
			if (((char *)info->content)[index.j] == ',')
			{
				if (state == 0)
				{
					r = atoi(&((char *)info->content)[index.j - (index.j - 2)]);
					index.p = index.j + 1;
				}
				else if (state == 1)
				{
					g = atoi(&((char *)info->content)[index.j - (index.j
								- index.p)]);
					b = atoi(&((char *)info->content)[index.j + 1]);
					break ;
				}
				state++;
			}
			index.j++;
		}
		if (index.i == 1)
			data->cColor = (0x00 << 24) | (r << 16) | (g << 8) | b;
		else
			data->fColor = (0x00 << 24) | (r << 16) | (g << 8) | b;
		state = 0;
		index.j = 2;
		info = info->next;
	}
}

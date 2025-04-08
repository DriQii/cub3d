/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:02:55 by evella            #+#    #+#             */
/*   Updated: 2025/04/08 00:52:31 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <parsing.h>

t_list	*ft_create_info(char *mapStr)
{
	t_list	*map_lst;
	int		map_fd;
	char	*tmp;

	map_lst = NULL;
	map_fd = open(mapStr, O_RDONLY);
	tmp = get_next_line(map_fd);
	while (tmp)
	{
		if (tmp[0] != '\n')
			ft_lstadd_back(&map_lst, ft_lstnew(tmp));
		else
			free(tmp);
		tmp = get_next_line(map_fd);
	}
	close(map_fd);
	return (map_lst);
}

int	ft_check_all(t_list *info)
{
	if (!ft_check_pole(info) || !ft_check_up_and_down(info))
		return (0);
	return (1);
}

int	ft_parsing(char **argv, t_data *data)
{
	t_list	*info;

	info = ft_create_info(argv[1]);
	data->map = ft_create_map(info, data);
	if (!ft_check_all(info) || !ft_check_map(data))
	{
		printf("ERROR : Wrong map.cub format\n");
		return (ft_freetabtabb(data->map), ft_freelst(info), 0);
	}
	data->info = info;
	return (1);
}

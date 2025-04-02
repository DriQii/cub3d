/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:02:55 by evella            #+#    #+#             */
/*   Updated: 2025/04/02 14:10:35 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <cub3d.h>

t_list *ft_create_info(char *mapStr)
{
	t_list	*mapLst;
	int		mapFd;
	char	*tmp;

	mapLst = NULL;
	mapFd = open(mapStr, O_RDONLY);
	tmp = get_next_line(mapFd);
	while(tmp)
	{
		ft_lstadd_back(&mapLst,ft_lstnew(tmp));
		tmp = get_next_line(mapFd);
	}
	close(mapFd);
	return (mapLst);
}

int ft_check_all(t_list *info)
{
	if (!ft_check_pole(info) || !ft_check_up_and_down(info))
		return(0);
	return(1);
}

int	ft_parsing(char **argv, t_data *data)
{
	t_list		*info;

	info = ft_create_info(argv[1]);
	data->map = ft_create_map(info, data);
	if (!ft_check_all(info) || !ft_check_map(info, data))
	{
		printf("ERROR : Wrong map.cub format\n");
		return (0);
	}
	data->info = info;
	return (1);
}



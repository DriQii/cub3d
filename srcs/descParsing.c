/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descParsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:39 by evella            #+#    #+#             */
/*   Updated: 2025/04/07 23:33:53 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_check_pole_line(char *str, char *carDir)
{
	int	len;

	len = ft_strlen(str);
	if (len < 11 || str[0] != carDir[0] || str[1] != carDir[1] || str[3] != '.'
		|| str[4] != '/' || str[len - 4] != 'x' || str[len - 3] != 'p'
		|| str[len - 2] != 'm')
		return (0);
	return (1);
}

int	ft_check_pole(t_list *map)
{
	int		i;
	char	*car_dir[4];

	car_dir[0] = ft_strdup("NO");
	car_dir[1] = ft_strdup("SO");
	car_dir[2] = ft_strdup("WE");
	car_dir[3] = ft_strdup("EA");
	i = 0;
	if (ft_lstsize(map) < 9)
		return (free(car_dir[0]), free(car_dir[1]), free(car_dir[2])
			, free(car_dir[3]), 0);
	while (i < 4)
	{
		if (!ft_check_pole_line(map->content, car_dir[i]))
			return (free(car_dir[0]), free(car_dir[1]), free(car_dir[2])
				, free(car_dir[3]), 0);
		i++;
		map = map->next;
	}
	return (free(car_dir[0]), free(car_dir[1]), free(car_dir[2])
		, free(car_dir[3]), 1);
}

int	ft_check_comma(char *str)
{
	t_index	index;

	index.i = 2;
	index.s = 0;
	index.p = 0;
	index.l = 0;
	while (str[index.i] != '\n')
	{
		if (index.s == 1 && (str[index.i] >= '0' && str[index.i] <= '9'))
			index.p++;
		else if (index.s == 0 && (str[index.i] >= '0'
				&& str[index.i] <= '9') && ++index.p)
			index.s = 1;
		if ((index.s == 0 && (str[index.i] < '0' || str[index.i] > '9'))
			|| (index.s == 1 && ((str[index.i] < '0' || str[index.i] > '9')
					&& str[index.i] != ',')) || index.p >= 4
			|| (str[index.i] == ',' && index.p == 0))
			return (0);
		if (str[index.i++] == ',' && ++index.l)
			index.p = 0;
	}
	if ((index.l != 2 || str[index.i - 1] == ','))
		return (0);
	else
		return (1);
}

int	ft_check_up_and_down(t_list *map)
{
	int		i;
	char	*up;
	char	*down;

	i = 0;
	while (i++ < 4)
		map = map->next;
	up = map->content;
	down = map->next->content;
	if (up[0] != 'F' || down[0] != 'C' || !ft_check_comma(up)
		|| !ft_check_comma(down))
		return (0);
	return (1);
}

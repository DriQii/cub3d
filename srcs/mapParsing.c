/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapParsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:22 by evella            #+#    #+#             */
/*   Updated: 2025/02/19 15:40:17 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static char *ft_add_space_to_str(char *str, int len)
{
	char	*tmp;
	tmp = ft_calloc(sizeof(char), len + 1);
	ft_memset(tmp, ' ', len);
	ft_strcpy(tmp, str);
	tmp[ft_strlen(str) - 1] = ' ';
	tmp[ft_strlen(str)] = ' ';
	tmp[ft_strlen(tmp) - 1] = '\n';
	free(str);
	return (tmp);
}

static void ft_add_space_to_tab(t_data *data)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	index.l = 0;

	index.l = ft_strlen(data->map[0]);
	while(data->map[index.i])
	{
		if (ft_strlen(data->map[index.i]) > index.l)
			index.l = ft_strlen(data->map[index.i]);
		index.i++;
	}
	index.i = 0;
	while(data->map[index.i])
	{
		if (ft_strlen(data->map[index.i]) < index.l)
			data->map[index.i] = ft_add_space_to_str(data->map[index.i], index.l);
		index.i++;
	}
}

static int ft_check_space(char** map,int i, int j)
{
	if(map[i][j + 1] == ' ' || map[i][j + 1] == '\n')
		return(0);
	else if(j == 0 || map[i][j - 1] == ' ')
		return(0);
	else if(!map[i + 1] || map[i + 1][j] == ' ')
		return(0);
	else if(i == 0 || map[i - 1][j] == ' ')
		return(0);
	return (1);
}

int ft_check_map(t_list *info, t_data *data)
{
	t_index	index;

	index.p = 0;
	index.i = 0;
	index.j = 0;
	ft_add_space_to_tab(data);
	while(data->map[index.i])
	{
		while(data->map[index.i][index.j])
		{
			if(data->map[index.i][index.j] == '0')
				if (!ft_check_space(data->map, index.i, index.j))
					return(0);
			index.j++;
		}
		index.j = 0;
		index.i++;
	}
	return (1);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:32 by evella            #+#    #+#             */
/*   Updated: 2025/02/17 19:18:33 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void ft_print_tabtab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		printf("%s", tab[i++]);
	printf("\n");
}

char **ft_create_map(t_list *info)
{
	t_index index;
	char **map;

	map = ft_calloc(sizeof(char *) , ft_lstsize(info) - 7);
	index.i = 0;
	while (index.i++ < 8)
		info = info->next;
	index.i = 0;
	while(info)
	{
		map[index.i] = ft_strdup(info->content);
		info = info->next;
		index.i++;
	}
	map[index.i] = NULL;
	return(map);
}


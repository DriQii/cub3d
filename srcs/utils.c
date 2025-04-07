/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:32 by evella            #+#    #+#             */
/*   Updated: 2025/04/07 23:23:44 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_print_tabtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s", tab[i++]);
	printf("\n");
}

char	**ft_create_map(t_list *info, t_data *data)
{
	t_index	index;
	char	**map;

	data->mapY = 8;
	map = ft_calloc(sizeof(char *), ft_lstsize(info) - 5);
	index.i = 0;
	while (index.i++ < 6)
		info = info->next;
	index.i = 0;
	while (info)
	{
		map[index.i] = ft_strdup(info->content);
		info = info->next;
		index.i++;
	}
	map[index.i] = NULL;
	return (map);
}

void	*ft_freetabtabb(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (i > 0)
		free(tab);
	tab = NULL;
	return (NULL);
}

void	ft_freelst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	free(lst);
}

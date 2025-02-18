#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdio.h>
#include <mlx.h>
#include <libft.h>
#include <fcntl.h>
#include <cub3d.h>
#include <math.h>

typedef struct s_index
{
	int	i;
	int j;
	int	l;
	int k;
	int	x;
	int	y;
	int	p;
	int	s;
	int	e;
	int	c;

}	t_index;

int ft_check_pole(t_list *map);
int ft_check_up_and_down(t_list *map);
void ft_print_tabtab(char **tabtab);

#endif

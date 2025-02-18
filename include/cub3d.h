#ifndef CUB3D_H
#define CUB3D_H

#define WIN_WIDTH 1080
#define WIN_LENGHT 720

#include <unistd.h>
#include <stdio.h>
#include <mlx.h>
#include <libft.h>
#include <fcntl.h>
#include <parsing.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_minimap
{
	int		length;
	int		width;
	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	delta;
}	t_minimap;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;

}	t_player;

typedef enum e_key
{
	W,
	A,
	S,
	D,
}			t_key;

typedef struct s_data
{
	t_minimap	*minimap;
	t_list		*info;
	t_player	player;
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			keystate[4];
}	t_data;

char		**ft_create_map(t_list *info);
int			ft_parsing(char **argv, t_data *data);
int			keyDown(int keycode, t_data *data);
int			keyUp(int keycode, t_data *data);
void		ft_init_minimap(t_data *data);
int			ft_print_minimap(t_data *data);
void		ft_init_pos(t_data *data);
int			ft_check_map(t_list *info, t_data *data);
void	ft_moove_pos(t_data *data);
void	ft_put_fov(t_data *data);




#endif

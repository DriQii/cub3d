#ifndef CUB3D_H
#define CUB3D_H

#define WIN_WIDTH 1080
#define WIN_LENGHT 720
#define TILE_SIZE 64

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

typedef enum e_key
{
	W,
	A,
	S,
	D,
	R,
	L,
}			t_key;


typedef struct s_minimap
{
	t_img	floor;
	t_img	wall;
	t_img 	player;
	t_img	fov;
}				t_minimap;

typedef struct s_player
{
	float	x;
	float	y;
	float	rx;
	float	ry;
	float	pa;
	float	speed;
	int		yo;
	int		xo;
}				t_player;

typedef struct s_mouse
{
	float x;
	float y;
	float newX;
	float newY;
}				t_mouse;

typedef struct s_data
{
	t_list		*info;
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_minimap	minimap;
	t_player	player;
	int			keyState[6];
	t_mouse		mouse;
	t_img		frame;
	int			mapY;
	int			mapX;
}				t_data;

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	x;
	int	y;
	int	s;
	int	p;

}	t_index;

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

void		my_player_pixel_put(t_img *data, int x, int y, int color);
void		ft_create_minimap(t_data *data);
int			ft_render(t_data *data);
void		my_pixel_put(t_img *data, int x, int y, int color);
void		my_4x4_pixel_put(t_img *data, int x, int y, int color);
void		ft_moove_pos(t_data *data);
void		ft_moove_fov(t_data *data);
int			MouseMoove(int x, int y, t_data *data);
int			KeyUp(int keycode, t_data *data);
int			KeyDown(int keycode, t_data *data);
char		**ft_create_map(t_list *info, t_data *data);
int			ft_parsing(char **argv, t_data *data);
int			ft_check_map(t_list *info, t_data *data);
void		ft_init(t_data *data);


#endif

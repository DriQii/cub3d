#ifndef CUB3D_H
#define CUB3D_H

#define WIN_WIDTH 1280
#define WIN_LENGHT 800
#define FOVDEG 65
#define FOVRAD FOVDEG * M_PI / 180
#define WALL_WIDHT 1284
#define WALL_HEIGHT 1283

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
	int			keyState[6];
	int			mapX;
	int			mapY;
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_img		wall;
	t_img		frame;
	t_list		*info;
	t_mouse		mouse;
	t_player	player;
	t_minimap	minimap;
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

typedef struct s_ray
{
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		texX;
	int		texY;
	int		wallLen;
	int		wStart;
	int		wEnd;
	char	finalDir;
	float	step;
	float	impact;
	float	rayDirX;
	float	rayDirY;
	float	deltaX;
	float	deltaY;
	float	sideDistX;
	float	sideDistY;
	float	finalDist;
}	t_ray;

void 		ft_dda_loop(t_data *data, t_ray *ray);
void 		ft_init_side_dist(t_data *data, t_ray *ray, float angle);
t_ray		ft_find_dist(t_data *data, float angle);
float		ft_find_impact(t_ray ray, t_data *data, float angle);
void		ft_set_index(t_data *data, t_ray *ray, t_index *index, float angle);
void		ft_print_bg(t_data *data, int x, int wallen);
void		ft_create_fov(t_data *data);
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

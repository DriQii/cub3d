#include <cub3d.h>

int	KeyDown(int keycode, t_data *data)
{
	printf("Keydown : %d\n", keycode);
	if (keycode == 13)
		data->keyState[W] = 1;
	if (keycode == 0)
		data->keyState[A] = 1;
	if (keycode == 1)
		data->keyState[S] = 1;
	if (keycode == 2)
		data->keyState[D] = 1;
	if (keycode == 123)
		data->keyState[L] = 1;
	if (keycode == 124)
		data->keyState[R] = 1;
	return (0);
}

int	KeyUp(int keycode, t_data *data)
{
	printf("KeyUp : %d\n", keycode);
	if (keycode == 13)
		data->keyState[W] = 0;
	if (keycode == 0)
		data->keyState[A] = 0;
	if (keycode == 1)
		data->keyState[S] = 0;
	if (keycode == 2)
		data->keyState[D] = 0;
	if (keycode == 123)
		data->keyState[L] = 0;
	if (keycode == 124)
		data->keyState[R] = 0;
	return (0);
}

int	MouseMoove(int x, int y, t_data *data)
{
	if (x < data->mouse.x)
		data->player.pa -= 0.1;
	if (x > data->mouse.x)
		data->player.pa += 0.1;
	data->mouse.x = x;
	return (0);
}

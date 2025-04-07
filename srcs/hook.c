#include <cub3d.h>

int	KeyDown(int keycode, t_data *data)
{
	printf("k = %d\n", keycode);
	if (keycode == WK)
		data->keyState[W] = 1;
	if (keycode == AK)
		data->keyState[A] = 1;
	if (keycode == SK)
		data->keyState[S] = 1;
	if (keycode == DK)
		data->keyState[D] = 1;
	if (keycode == LK)
		data->keyState[L] = 1;
	if (keycode == RK)
		data->keyState[R] = 1;
	return (0);
}

int	KeyUp(int keycode, t_data *data)
{
	printf("k = %d\n", keycode);
	if (keycode == WK)
		data->keyState[W] = 0;
	if (keycode == AK)
		data->keyState[A] = 0;
	if (keycode == SK)
		data->keyState[S] = 0;
	if (keycode == DK)
		data->keyState[D] = 0;
	if (keycode == LK)
		data->keyState[L] = 0;
	if (keycode == RK)
		data->keyState[R] = 0;
	return (0);
}

int	MouseMoove(int x, int y, t_data *data)
{
	if (x < data->mouse.x - 2)
		data->player.pa -= 0.1;
	if (x > data->mouse.x + 2)
		data->player.pa +=0.1;
	data->mouse.x = x;
	return (0);
}

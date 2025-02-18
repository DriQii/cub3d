#include <cub3d.h>

int keyDown(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keystate[W] = 1;
	else if (keycode == 0)
		data->keystate[A] = 1;
	else if (keycode == 1)
		data->keystate[S] = 1;
	else if (keycode == 2)
		data->keystate[D] = 1;
	return (0);
}
int keyUp(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keystate[W] = 0;
	else if (keycode == 0)
		data->keystate[A] = 0;
	else if (keycode == 1)
		data->keystate[S] = 0;
	else if (keycode == 2)
		data->keystate[D] = 0;
	return (0);
}

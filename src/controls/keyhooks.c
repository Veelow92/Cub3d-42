/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:25 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 15:54:02 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../minilibx-linux/mlx.h"
#include "../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>

// ############################################################################
//								KeyHooks
// ############################################################################
void	move_key(t_data *data)
{
	if (data->player.key_w)
		w_key(data);
	if (data->player.key_s)
		s_key(data);
	if (data->player.key_a)
		a_key(data);
	if (data->player.key_d)
		d_key(data);
	if (data->player.key_left || data->player.key_right)
		lr_key(data);
}

int	valid_tile(t_data *data, double y, double x)
{
	char			tile;
	const double	bounds = 0.2;
	const int		d[2] = {-1, 1};
	int				i[4];

	i[0] = -1;
	while (++i[0] < 2)
	{
		i[1] = -1;
		while (++i[1] < 2)
		{
			i[2] = (int)(y + d[i[0]] * bounds);
			i[3] = (int)(x + d[i[1]] * bounds);
			if (i[2] < 0 || i[2] >= data->map.y_size)
				return (0);
			if (i[3] < 0 || i[3] >= (int)ft_strlen(data->map.maps[i[2]]))
				return (0);
			tile = data->map.maps[i[2]][i[3]];
			if (!(tile == '0' || tile == 'N' || tile == 'S' || tile == 'W'
					|| tile == 'E'
					|| (tile == 'D' && data->map.door_open[i[2]][i[3]] == 1)))
				return (0);
		}
	}
	return (1);
}

int	key_press(int key, t_data *data)
{
	if (key == XK_w || key == XK_W)
		data->player.key_w = 1;
	if (key == XK_s || key == XK_S)
		data->player.key_s = 1;
	if (key == XK_a || key == XK_A)
		data->player.key_a = 1;
	if (key == XK_d || key == XK_D)
		data->player.key_d = 1;
	if (key == XK_Up)
		data->player.key_up = 1;
	if (key == XK_Down)
		data->player.key_down = 1;
	if (key == XK_Left)
		data->player.key_left = 1;
	if (key == XK_Right)
		data->player.key_right = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_w || key == XK_W)
		data->player.key_w = 0;
	if (key == XK_s || key == XK_S)
		data->player.key_s = 0;
	if (key == XK_a || key == XK_A)
		data->player.key_a = 0;
	if (key == XK_d || key == XK_D)
		data->player.key_d = 0;
	if (key == XK_e || key == XK_E)
		try_toggle_door(data);
	if (key == XK_Up)
		data->player.key_up = 0;
	if (key == XK_Down)
		data->player.key_down = 0;
	if (key == XK_Left)
		data->player.key_left = 0;
	if (key == XK_Right)
		data->player.key_right = 0;
	if (key == XK_Escape || key == XK_q)
		close_exit(data);
	return (0);
}

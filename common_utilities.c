/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:24:50 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/26 13:42:54 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	interpolate_color(int color1, int color2, double t)
{
	int	r;
	int	g;
	int	b;
	int	temp_start;
	int	temp_finish;

	temp_start = (color1 >> 16) & 0xFF;
	temp_finish = (color2 >> 16) & 0xFF;
	r = (int)(temp_start + t * (temp_finish - temp_start));
	temp_start = (color1 >> 8) & 0xFF;
	temp_finish = (color1 >> 8) & 0xFF;
	g = (int)(temp_start + t * (temp_finish - temp_start));
	temp_start = color1 & 0xFF;
	temp_finish = color2 & 0xFF;
	b = (int)(temp_start + t * (temp_finish - temp_start));
	return ((r << 16) + (g << 8) + b);
}

/*Blue
Indigo
Pink
Yellow
Orange
Red*/

int	get_color(int iter)
{
	int		palette[6];
	double	t;
	int		index;
	double	local_t;

	palette[0] = 0x0000FF;
	palette[1] = 0x4B0082;
	palette[2] = 0xFFC0CB;
	palette[3] = 0xFFFF00;
	palette[4] = 0xFFA500;
	palette[5] = 0xFF0000;
	if (iter == MAX_ITER)
		return (0x000000);
	t = (double)iter / MAX_ITER;
	index = (int)(t * (6 - 1));
	local_t = (t * (6 - 1)) - index;
	return (interpolate_color(palette[index], palette[index + 1], local_t));
}

void	drawhelper(t_main_obj *obj, int iter, int x, int y)
{
	int	color;
	int	pixel_index;

	if (iter == MAX_ITER)
		color = 0x000000;
	else
		color = get_color(iter);
	pixel_index = (y * obj->sl1) + (x * obj->bpp1 / 8);
	obj->img_data[pixel_index] = color & 0xFF;
	obj->img_data[pixel_index + 1] = (color >> 8) & 0xFF;
	obj->img_data[pixel_index + 2] = (color >> 16) & 0xFF;
}
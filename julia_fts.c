/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:39:10 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 14:30:51 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(double real, double comp, double real_num, double complex_num)
{
	double	z_real_temp;
	int		n;

	n = 0;
	while (real * real + comp * comp <= 4 && n < MAX_ITER)
	{
		z_real_temp = real * real - comp * comp + real_num;
		comp = 2 * real * comp + complex_num;
		real = z_real_temp;
		n++;
	}
	return (n);
}

int	drawhelper(main_obj *obj, int iter, int x, int y)
{
	int	color;
	int	brightness;
	int	pixel_index;

	if (iter == MAX_ITER)
		color = 0x000000;
	else
	{
		brightness = 255 * iter / MAX_ITER;
		color = (brightness << 16) + (brightness << 8) + brightness;
	}
	pixel_index = (y * obj->sl1) + (x * obj->bpp1 / 8);
	obj->img_data[pixel_index] = color;
	obj->img_data[pixel_index + 1] = (color >> 8);
	obj->img_data[pixel_index + 2] = (color >> 16);
}

void	draw_julia(main_obj *obj, double real_num, double complex_num)
{
	int		x;
	int		y;
	int		n;
	double	real;
	double	imag;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			real = obj->math_num.real_num.min + (x + obj->math_num.x_offset) * (obj->math_num.real_num.max - obj->math_num.real_num.min) / WIN_WIDTH;
			imag = obj->math_num.imag_num.min + (y + obj->math_num.y_offset) * (obj->math_num.imag_num.max - obj->math_num.imag_num.min) / WIN_HEIGHT;
			n = julia(real, imag, real_num, complex_num);
			drawhelper(obj, n, x, y);
			x++;
		}
		y++;
	}
}

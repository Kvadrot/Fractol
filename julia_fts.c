/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:39:10 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 17:37:31 by itykhono         ###   ########.fr       */
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

void	draw_julia(t_main_obj *obj, double real_num, double complex_num)
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

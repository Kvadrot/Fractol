/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_fts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:32:50 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 17:37:17 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" 

t_math_val	init_mandelbrot_limits(void)
{
	t_math_val	main_set;

	main_set.real_num.min = -2.0;
	main_set.real_num.max = 2.0;
	main_set.imag_num.min = -2.0;
	main_set.imag_num.max = 2.0;
	main_set.x_offset = 0;
	main_set.y_offset = 0;
	return (main_set);
}

int	mandelbrot(double real, double imag)
{
	double	z_real;
	double	z_imag;
	double	z_real_temp;
	int		n;

	z_real = 0;
	z_imag = 0;
	z_real_temp = 0;
	n = 0;
	while (z_real * z_real + z_imag * z_imag <= 4 && n < MAX_ITER)
	{
		z_real_temp = z_real * z_real - z_imag * z_imag + real;
		z_imag = 2 * z_real * z_imag + imag;
		z_real = z_real_temp;
		n++;
	}
	return (n);
}

void	draw_mandelbrot(t_main_obj *obj)
{
	int		n;
	int		x;
	int		y;
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
			n = mandelbrot(real, imag);
			drawhelper(obj, n, x, y);
			x++;
		}
		y++;
	}
}

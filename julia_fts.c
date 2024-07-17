/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:39:10 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 14:11:01 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(double real, double comp, double real_num, double complex_num)
{
    int n;

	n = 0;
	while (real * real + comp * comp <= 4 && n < MAX_ITER)
    {
        double z_real_temp = real * real - comp * comp + real_num;
        comp = 2 * real * comp + complex_num;
        real = z_real_temp;
        n++;
    }
    return n;
}

void draw_julia(main_obj *obj, double real_num, double complex_num)
{
    int x, y, color;
    for (y = 0; y < WIN_HEIGHT; y++)
    {
        for (x = 0; x < WIN_WIDTH; x++)
        {
            double real = obj->math_num.real_num.min + (x + obj->math_num.x_offset) * (obj->math_num.real_num.max - obj->math_num.real_num.min) / WIN_WIDTH;
            double imag = obj->math_num.imag_num.min + (y + obj->math_num.y_offset) * (obj->math_num.imag_num.max - obj->math_num.imag_num.min) / WIN_HEIGHT;
            int n = julia(real, imag, real_num, complex_num);

            // Map the number of iterations to a color
    		if (n == MAX_ITER)
            {
                color = 0x000000; // Black for points inside the set
            }
            else
            {
                int brightness = 255 * n / MAX_ITER;
                color = (brightness << 16) + (brightness << 8) + brightness; // Grayscale
            }

            int pixel_index = (y * obj->sl1) + (x * obj->bpp1 / 8);
            obj->img_data[pixel_index] = color;
            obj->img_data[pixel_index + 1] = (color >> 8);
            obj->img_data[pixel_index + 2] = (color >> 16);
        }
    }
}
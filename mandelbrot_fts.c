/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_fts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:32:50 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/15 15:51:16 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" 

math_val init_limits() {
    math_val main_set;
    main_set.real_num.min = -2.0;
    main_set.real_num.max = 2.0;
    main_set.imag_num.min = -2.0;
    main_set.imag_num.max = 2.0;
    main_set.x_offset = 0;
    main_set.y_offset = 0;
    return main_set;
}

int mandelbrot(double real, double imag) {
    double z_real = 0;
    double z_imag = 0;
    int n = 0;
    while (z_real * z_real + z_imag * z_imag <= 4 && n < MAX_ITER) {
        double z_real_temp = z_real * z_real - z_imag * z_imag + real;
        z_imag = 2 * z_real * z_imag + imag;
        z_real = z_real_temp;
        n++;
    }
    return n;
}

void draw_mandelbrot(int bpp1, int sl1, int endian1, char *data, math_val *math_val) {
    int x, y, color;
    for (y = 0; y < WIN_HEIGHT; y++) {
        for (x = 0; x < WIN_WIDTH; x++) {
            double real = math_val->real_num.min + (x + math_val->x_offset) * (math_val->real_num.max - math_val->real_num.min) / WIN_WIDTH;
            double imag = math_val->imag_num.min + (y + math_val->y_offset) * (math_val->imag_num.max - math_val->imag_num.min) / WIN_HEIGHT;
            int n = mandelbrot(real, imag);

            // Map the number of iterations to a color
            if (n == MAX_ITER) {
                color = 0x000000; // Black for points inside the set
            } else {
                int brightness = 255 / n * MAX_ITER;
                color = (brightness << 16) + (brightness << 8) + brightness; // Grayscale
            }

            int pixel_index = (y * sl1) + (x * bpp1 / 8);
            data[pixel_index] = color;
            data[pixel_index + 1] = (color >> 8);
            data[pixel_index + 2] = (color >> 16);
        }
    }
}
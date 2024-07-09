/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:45:13 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/09 13:08:13 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "mlx_int.h"
#include "fractol.h"


#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} mouse_pos;

typedef struct {
    double min;
    double max;
} min_max;

typedef struct {
    min_max real_num;
    min_max imag_num;
    double x_offset;
    double y_offset;
} math_val;

typedef struct {
    void *mlx;
    void *mlx_win;
    void *image;
    char *img_data;
    int bpp1;
    int sl1;
    int endian1;
    math_val math_num;
} main_obj;

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
            data[pixel_index] = color & 0xFF;
            data[pixel_index + 1] = (color >> 8) & 0xFF;
            data[pixel_index + 2] = (color >> 16) & 0xFF;
        }
    }
}

int buttons_tap_handler_hook(int key, void *p) {
   
    main_obj *obj;

    obj = (main_obj *)p;
    if (key == 0xFF1B)
        exit(0);
	else if (key == 65361) //left
	{
		obj->math_num.x_offset -= 24;
		printf("left\n");
	}	else if (key == 65363)//right
	{
		 printf("right\n");
		 obj->math_num.x_offset += 24;
	}	else if (key == 65362)//up
	{
		 printf("up\n");
		 obj->math_num.y_offset -= 24;
	}	else if (key == 65364)//down
	{
		 obj->math_num.y_offset += 24;
		 printf("down\n");
	}
    draw_mandelbrot(obj->bpp1, obj->sl1, obj->endian1, obj->img_data, &(obj->math_num));
	mlx_put_image_to_window(obj->mlx, obj->mlx_win, obj->image, 0, 0);
    return 0;
}

int close_cross_btn_tapped(void *p) {
    printf("WIN is CLOSED\n");
    exit(0);
    return 0;
}

double mod(double value, double modulus) {
    double result = fmod(value, modulus);
    if (result < 0) {
        result += modulus;
    }
    return result;
}

int zoom_hook(int button, int x, int y, void *p) {
    main_obj *obj;
    double zoom_factor;

    obj = (main_obj *)p;
	double mouse_real = obj->math_num.real_num.min + ((x + obj->math_num.x_offset) * (obj->math_num.real_num.max - obj->math_num.real_num.min) / WIN_WIDTH);
    double mouse_imag = obj->math_num.imag_num.min + ((y + 	obj->math_num.y_offset) * (obj->math_num.imag_num.max - obj->math_num.imag_num.min) / WIN_HEIGHT);

    if (button == 4) {  // Zoom in
        zoom_factor = 1 / ZOOM_STEP;
    } else if (button == 5) {  // Zoom out
        zoom_factor = ZOOM_STEP;
    } else {
        return 0;
    }

    obj->math_num.real_num.min = mouse_real + (obj->math_num.real_num.min - mouse_real) * zoom_factor;
    obj->math_num.real_num.max = mouse_real + (obj->math_num.real_num.max - mouse_real) * zoom_factor;
    obj->math_num.imag_num.min = mouse_imag + (obj->math_num.imag_num.min - mouse_imag) * zoom_factor;
    obj->math_num.imag_num.max = mouse_imag + (obj->math_num.imag_num.max - mouse_imag) * zoom_factor;

    draw_mandelbrot(obj->bpp1, obj->sl1, obj->endian1, obj->img_data, &(obj->math_num));
    mlx_put_image_to_window(obj->mlx, obj->mlx_win, obj->image, 0, 0);
    return 0;
}

int mouse_movement(int x, int y, void *p) {
    printf("Mouse moving in Win3, at %dx%d.\n", x, y);
    return 0;
}

main_obj ft_set_main_obj() {
    main_obj main_obj;

    main_obj.mlx = mlx_init();
    main_obj.mlx_win = mlx_new_window(main_obj.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
    main_obj.image = mlx_new_image(main_obj.mlx, WIN_WIDTH, WIN_HEIGHT);
    main_obj.img_data = mlx_get_data_addr(main_obj.image, &(main_obj.bpp1), &(main_obj.sl1), &(main_obj.endian1));
    main_obj.math_num = init_limits();

    return main_obj;
}

int main(int argc, char **argv) {
    main_obj main_obj;
    mouse_pos mouse_pos;

    main_obj = ft_set_main_obj();

    draw_mandelbrot(main_obj.bpp1, main_obj.sl1, main_obj.endian1, main_obj.img_data, &(main_obj.math_num));
    mlx_put_image_to_window(main_obj.mlx, main_obj.mlx_win, main_obj.image, 0, 0);

    mlx_mouse_hook(main_obj.mlx_win, zoom_hook, &(main_obj));
    mlx_key_hook(main_obj.mlx_win, buttons_tap_handler_hook, &(main_obj));
    mlx_hook(main_obj.mlx_win, 17, 0, close_cross_btn_tapped, &(main_obj));
    mlx_loop(main_obj.mlx);

    return 0;
}

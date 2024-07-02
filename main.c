/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:45:13 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/02 21:04:03 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#define WIN_WIDTH 500
#define WIN_HEIGHT 500
#define MAX_ITER 1000

#define COLORS

typedef struct Min_Max {
	double min;
	double max;
} min_max;

typedef struct MainSet {
	min_max real_num;
	min_max imag_num;
} limites;

limites init_limits()
{
	limites main_set;

	main_set.real_num.min = -2.0;
	main_set.real_num.max = 2.0;
	main_set.imag_num.min = -2.0;
	main_set.imag_num.max = 2.0;
}


int	test_hook(int key, int param)
{
	write(1, "done\n", 5);
	return (0);
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

void draw_mandelbrot(int bpp1, int sl1, int endian1, char *data) {
    int x, y, color;
    // double real_min = -0.39766558, real_max = 0.39766558;
    // double imag_min = -0.345005429, imag_max = 0.39766558;

	double real_min = -2.0, real_max = 2;
    double imag_min = -2, imag_max = 2;

    for (y = 0; y < WIN_HEIGHT; y++) {
        for (x = 0; x < WIN_WIDTH; x++) {
            // double real = real_min + (double)(x + 150) / WIN_WIDTH * (real_max - real_min);
            // double imag = imag_min + (double)(y + 50) / WIN_HEIGHT * (imag_max - imag_min);
			double real = real_min + (double)(x + 0) / WIN_WIDTH * (real_max - real_min);
            double imag = imag_min + (double)(y + 0) / WIN_HEIGHT * (imag_max - imag_min);
            int n = mandelbrot(real, imag);

            // Map the number of iterations to a color
            if (n == MAX_ITER) {
                color = 0x000000; // Black for points inside the set
			
            } else {
					//TODO: colorize pixels by iteration
                int brightness = 255 / n * MAX_ITER;
                color = (brightness << 16) + (brightness << 8) + brightness; // Grayscale
            }

			printf("sl1 = %d;\n bpp1 = %d\n", sl1, bpp1);
            int pixel_index = (y * sl1) + (x * bpp1 / 8);
            data[pixel_index] = color & 0xFF;
            data[pixel_index + 1] = (color >> 8) & 0xFF;
            data[pixel_index + 2] = (color >> 16) & 0xFF;
        }
    }
}

// void ft_my_menadelbrot(limites *math_num, int sl1, int bpp1, char *data)
// {
// 	double	x;
// 	double	y;
// 	double	temp;
// 	int		current_iteration;
// 	int		px;
// 	int		py;

// 	x = 0;
// 	y = 0;
// 	px = 0;
// 	py = 0;

// 	current_iteration = 0;
// 	// while (y < WIN_HEIGHT)
// 	// {
// 	// 	while (x < WIN_WIDTH)
// 	// 	{
			
// 	// 	}
// 	// }
// 	int tempo = 256 / MAX_ITER;

// 	while (py < WIN_HEIGHT)
// 	{
// 		while (px < WIN_WIDTH)
// 		{
// 			current_iteration = 0;
// 			while (x*x + y * y && current_iteration < MAX_ITER)
// 			{
// 				temp = x*x - y*y + math_num->real_num.min;
// 				y = 2*x*y + math_num->imag_num.min;
// 				x = temp;
// 				int color = (tempo * current_iteration << 16) + (tempo * current_iteration << 8) + tempo * current_iteration;
// 				int pixel_index = (y * sl1) + (x * bpp1 / 8);
//             	data[pixel_index] = color;
//            		data[pixel_index + 1] = (color >> 8);
//            	 	data[pixel_index + 2] = (color >> 16);
// 				current_iteration++;
// 			}
// 			px++;
// 		}
// 		py++;
// 	}

// }

int main(int argc, char **argv)
{

	void	*mlx;
	void	*mlx_win;
	void	*image;
	char	*img_data;
	int		bpp1;
	int		sl1;
	int		endian1;
	limites	math_num;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "name_test");

	mlx_key_hook(mlx_win, test_hook, (void *)0);
	if (!(image = mlx_new_image(mlx,WIN_WIDTH,WIN_HEIGHT)))
    {
      printf(" !! KO !!\n");
      exit(1);
    }
	
	img_data = mlx_get_data_addr(image,&bpp1,&sl1,&endian1);
	// color_map(mlx_win, WIN_WIDTH, WIN_HEIGHT, mlx);
	draw_mandelbrot(bpp1, sl1, endian1, img_data);
	// math_num = init_limits();
	// ft_my_menadelbrot(&math_num, sl1, bpp1, img_data);

	mlx_put_image_to_window(mlx,mlx_win,image,0,0);
	mlx_loop(mlx);
}
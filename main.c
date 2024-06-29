/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:45:13 by itykhono          #+#    #+#             */
/*   Updated: 2024/06/29 19:45:18 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#define WIN_WIDTH 700
#define WIN_HEIGHT 700
#define MAX_ITER 1000

int	test_hook(int key, int param)
{
	write(1, "done\n", 5);
	return (0);
}

int	color_map(void *win,int w,int h, void *mlx)
{
  int	x;
  int	y;
  int	color;

  x = w;
  while (x--)
	{
		y = h;
		while (y--)
		{
			int red = 250;
			int green = 0;
			int blue = 0;
			
			color = (red << 16) + (green << 8) + blue;
			mlx_pixel_put(mlx,win,x,y,color);
		}
	}
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
    double real_min = -2.0, real_max = 2.0;
    double imag_min = -2.0, imag_max = 2.0;

    for (y = 0; y < WIN_HEIGHT; y++) {
        for (x = 0; x < WIN_WIDTH; x++) {
            double real = real_min + (double)x / WIN_WIDTH * (real_max - real_min);
            double imag = imag_min + (double)y / WIN_HEIGHT * (imag_max - imag_min);
            int n = mandelbrot(real, imag);

            // Map the number of iterations to a color
            if (n == MAX_ITER) {
                color = 0x000000; // Black for points inside the set
            } else {
                int brightness = 255;
                color = (brightness << 16) + (brightness << 8) + brightness; // Grayscale
            }

            int pixel_index = (y * sl1) + (x * bpp1 / 8);
            data[pixel_index] = color & 0xFF;
            data[pixel_index + 1] = (color >> 8) & 0xFF;
            data[pixel_index + 2] = (color >> 16) & 0xFF;
        }
    }
}

int main(int argc, char **argv)
{

	void	*mlx;
	void	*mlx_win;
	void	*image;
	char	*img_data;
	int		bpp1;
	int		sl1;
	int		endian1;

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
	mlx_put_image_to_window(mlx,mlx_win,image,0,0);
	

	mlx_loop(mlx);
}
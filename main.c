/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:45:13 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 10:44:04 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Function declarations
void draw_mandelbrot(int bpp, int sl, int endian, char *img_data, math_val *math);
void draw_julia(main_obj *obj, double real_num, double complex_num);
void destroy_app(void *p);
int buttons_tap_handler_hook(int key, void *p);
int close_cross_btn_tapped(void *p);
int zoom_hook(int button, int x, int y, void *p);
main_obj ft_set_main_obj(int fractal_id, char **argv, int argc);
int handle_input(int argc, char **argv);

void destroy_app(void *p)
{
    main_obj *obj = (main_obj *)p;
    mlx_destroy_image(obj->mlx, obj->image);
    mlx_destroy_window(obj->mlx, obj->mlx_win);
    mlx_destroy_display(obj->mlx);
    free(obj->mlx);
    exit(0);
}

int julia(double real, double comp, double real_num, double complex_num)
{
    int n = 0;
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

int buttons_tap_handler_hook(int key, void *p)
{
    main_obj *obj = (main_obj *)p;
    if (key == 0xFF1B)
        destroy_app(obj);
    else if (key == 65361)
        obj->math_num.x_offset -= 24;
    else if (key == 65363)
        obj->math_num.x_offset += 24;
    else if (key == 65362)
        obj->math_num.y_offset -= 24;
    else if (key == 65364)
        obj->math_num.y_offset += 24;

    if (obj->fractal_id == MANDELBROT_ID)
	{
        draw_mandelbrot(obj->bpp1, obj->sl1, obj->endian1, obj->img_data, &(obj->math_num));
	}
    else if (obj->fractal_id == JULIA_ID){
        draw_julia(obj, obj->julia_real, obj->julia_imag);
	}
    mlx_put_image_to_window(obj->mlx, obj->mlx_win, obj->image, 0, 0);
    return 0;
}

int close_cross_btn_tapped(void *p)
{
    destroy_app(p);
    return 0;
}

int zoom_hook(int button, int x, int y, void *p)
{
    main_obj *obj = (main_obj *)p;
    double zoom_factor;

    double mouse_real = obj->math_num.real_num.min + ((x + obj->math_num.x_offset) * (obj->math_num.real_num.max - obj->math_num.real_num.min) / WIN_WIDTH);
    double mouse_imag = obj->math_num.imag_num.min + ((y + obj->math_num.y_offset) * (obj->math_num.imag_num.max - obj->math_num.imag_num.min) / WIN_HEIGHT);

    if (button == 4)
    {
        zoom_factor = 1 / ZOOM_STEP;
    }
    else if (button == 5)
    {
        zoom_factor = ZOOM_STEP;
    }
    else
    {
        return 0;
    }

    obj->math_num.real_num.min = mouse_real + (obj->math_num.real_num.min - mouse_real) * zoom_factor;
    obj->math_num.real_num.max = mouse_real + (obj->math_num.real_num.max - mouse_real) * zoom_factor;
    obj->math_num.imag_num.min = mouse_imag + (obj->math_num.imag_num.min - mouse_imag) * zoom_factor;
    obj->math_num.imag_num.max = mouse_imag + (obj->math_num.imag_num.max - mouse_imag) * zoom_factor;

    if (obj->fractal_id == MANDELBROT_ID)
        draw_mandelbrot(obj->bpp1, obj->sl1, obj->endian1, obj->img_data, &(obj->math_num));
    else if (obj->fractal_id == JULIA_ID)
        draw_julia(obj, obj->julia_real, obj->julia_imag);

    mlx_put_image_to_window(obj->mlx, obj->mlx_win, obj->image, 0, 0);
    return 0;
}

int	atod(char *str_num, double *save_to)
{
	int i = 0;
	int tens;
	double integer_temp;
	double fractinal_temp;
	int sign;

	tens = 1;
	integer_temp = 0;
	fractinal_temp = 0;
	//TODO: handle int MAX
	while (str_num[i] >= '0' && str_num[i] <= '9')
	{
		integer_temp *= 10;
		integer_temp += ft_atoi(str_num);
		i++;
	}
	if (str_num[i] == '.') {
		i++;
		while (str_num[i] >= '0' && str_num[i] <= '9')
		{
			fractinal_temp /= 10;
			fractinal_temp += ft_atoi(str_num);
			i++;
			tens *= 10;
		}
	} else {
		return (404);
	}
	*save_to = integer_temp + (fractinal_temp / tens);
	printf("save_to = %f", *save_to);
	return (200);
}

main_obj ft_set_main_obj(int fractal_id, char **argv, int argc)
{
    main_obj main_obj;

    main_obj.mlx = mlx_init();
    main_obj.mlx_win = mlx_new_window(main_obj.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
    main_obj.image = mlx_new_image(main_obj.mlx, WIN_WIDTH, WIN_HEIGHT);
    main_obj.img_data = mlx_get_data_addr(main_obj.image, &(main_obj.bpp1), &(main_obj.sl1), &(main_obj.endian1));

    if (fractal_id == MANDELBROT_ID)
    {
        main_obj.math_num = init_mandelbrot_limits();
        main_obj.fractal_id = MANDELBROT_ID;
    }
    else if (fractal_id == JULIA_ID)
    {
        main_obj.fractal_id = JULIA_ID;
        main_obj.math_num = init_mandelbrot_limits();
        if (argc == 4)
        {
			//TODO: add FT_ATOI
            main_obj.julia_real = atod(argv[2], &(main_obj.julia_real));
            main_obj.julia_imag = atod(argv[3], &(main_obj.julia_imag));
        }
        else
        {
            main_obj.julia_real = -0.7;
            main_obj.julia_imag = 0.27015;
        }
    }

    return main_obj;
}

int handle_input(int argc, char **argv)
{
    if (argc == 2 || argc == 4)
    {
        if (ft_strcmp(argv[1], "mandel") == 0)
        {
            return MANDELBROT_ID;
        }
        else if (ft_strcmp(argv[1], "jul") == 0)
        {
            return JULIA_ID;
        }
    }
    else
    {
        write(1, "\nWrong parameters!\n", 19);
        write(1, "Example:\n ./fractol mandel\n", ft_strlen("Example:\n ./fractol mandel\n"));
        write(1, "Or\n ./fractol jul 0.312331 0.312414\n", ft_strlen("Or\n ./fractol jul 0.312331 0.312414\n"));
        return 404;
    }
    return 404;
}

int main(int argc, char **argv)
{
    int fractal_id = handle_input(argc, argv);
    if (fractal_id == 404)
        return 0;

    main_obj main_obj = ft_set_main_obj(fractal_id, argv, argc);

    if (fractal_id == MANDELBROT_ID)
        draw_mandelbrot(main_obj.bpp1, main_obj.sl1, main_obj.endian1, main_obj.img_data, &(main_obj.math_num));
    else if (fractal_id == JULIA_ID)
        draw_julia(&main_obj, main_obj.julia_real, main_obj.julia_imag);

    mlx_put_image_to_window(main_obj.mlx, main_obj.mlx_win, main_obj.image, 0, 0);
    mlx_mouse_hook(main_obj.mlx_win, zoom_hook, &(main_obj));
    mlx_key_hook(main_obj.mlx_win, buttons_tap_handler_hook, &(main_obj));

    mlx_hook(main_obj.mlx_win, 17, 0, close_cross_btn_tapped, &(main_obj));
    mlx_loop(main_obj.mlx);

    return 0;
}

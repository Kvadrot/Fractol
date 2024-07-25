/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:45:13 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/25 17:14:46 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void destroy_app(t_main_obj *obj, int exit_id)
{
	if (!obj)
		exit(exit_id);
	if (obj->mlx != NULL && obj->image != NULL)
		mlx_destroy_image(obj->mlx, obj->image);
	if (obj->mlx_win != NULL)
		mlx_destroy_window(obj->mlx, obj->mlx_win);
	if (obj->mlx != NULL)
		mlx_destroy_display(obj->mlx);
	if (obj->mlx != NULL)
		free(obj->mlx);
	exit(exit_id);
}

int	buttons_tap_handler_hook(int key, void *p)
{
	t_main_obj	*obj;

	obj = (t_main_obj *)p;
	if (key == 0xFF1B)
		destroy_app(obj, 0);
	else if (key == 65361)
		obj->math_num.x_offset -= 24;
	else if (key == 65363)
		obj->math_num.x_offset += 24;
	else if (key == 65362)
		obj->math_num.y_offset -= 24;
	else if (key == 65364)
		obj->math_num.y_offset += 24;
	if (obj->fractal_id == MANDELBROT_ID)
		draw_mandelbrot(obj);
	else if (obj->fractal_id == JULIA_ID)
		draw_julia(obj, obj->julia_real, obj->julia_imag);
	mlx_put_image_to_window(obj->mlx, obj->mlx_win, obj->image, 0, 0);
	return (0);
}

int	close_cross_btn_tapped(void *p)
{
	destroy_app(p, 0);
	return (0);
}

int	zoom_hook(int button, int x, int y, void *p)
{
	t_main_obj	*obj;
	double		zoom_factor;
	double		mouse_real;
	double		mouse_imag;

	obj = (t_main_obj *)p;
	mouse_real = obj->math_num.real_num.min + ((x + obj->math_num.x_offset) * (obj->math_num.real_num.max - obj->math_num.real_num.min) / WIN_WIDTH);
	mouse_imag = obj->math_num.imag_num.min + ((y + obj->math_num.y_offset) * (obj->math_num.imag_num.max - obj->math_num.imag_num.min) / WIN_HEIGHT);
	if (button == 4)
		zoom_factor = 1 / ZOOM_STEP;
	else if (button == 5)
		zoom_factor = ZOOM_STEP;
	else
		return (0);
	obj->math_num.real_num.min = mouse_real + (obj->math_num.real_num.min - mouse_real) * zoom_factor;
	obj->math_num.real_num.max = mouse_real + (obj->math_num.real_num.max - mouse_real) * zoom_factor;
	obj->math_num.imag_num.min = mouse_imag + (obj->math_num.imag_num.min - mouse_imag) * zoom_factor;
	obj->math_num.imag_num.max = mouse_imag + (obj->math_num.imag_num.max - mouse_imag) * zoom_factor;
	if (obj->fractal_id == MANDELBROT_ID)
		draw_mandelbrot(obj);
	else if (obj->fractal_id == JULIA_ID)
		draw_julia(obj, obj->julia_real, obj->julia_imag);
	mlx_put_image_to_window(obj->mlx, obj->mlx_win, obj->image, 0, 0);
	return (0);
}

void	convert_input_and_save(t_main_obj *main_obj, char **argv)
{
	if (validate_jul_param(argv[2]) == 200 && (validate_jul_param(argv[3])) == 200) 
	{
		ft_atod(argv[2], &(main_obj->julia_real));
		ft_atod(argv[3], &(main_obj->julia_imag));
	} else {
		write(1, "checkup example of input again", 31);
		destroy_app(main_obj, 12345);
	}
}

t_main_obj	ft_set_main_obj(int fractal_id, char **argv, int argc)
{
	t_main_obj	main_obj;

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
			convert_input_and_save(&main_obj, argv);
		else
		{
			main_obj.julia_real = 0.4;
			main_obj.julia_imag = 0.4;
		}
	}
	return (main_obj);
}

int	handle_input(int argc, char **argv)
{
	if (argc == 2 || argc == 4)
	{
		if (ft_strcmp(argv[1], "mandel") == 0)
			return (MANDELBROT_ID);
		else if (ft_strcmp(argv[1], "jul") == 0)
			return (JULIA_ID);
	}
	else
	{
		write(1, "\nWrong parameters!\n", 19);
		write(1, "Example:\n ./fractol mandel\n", ft_strlen("Example:\n ./fractol mandel\n"));
		write(1, "Or\n ./fractol jul 0.312331 0.312414\n", ft_strlen("Or\n ./fractol jul 0.312331 0.312414\n"));
		return (404);
	}
}

int	main(int argc, char **argv)
{
	int			fractal_id;
	t_main_obj	main_obj;

	fractal_id = handle_input(argc, argv);
	if (fractal_id == 404)
		return (0);
	main_obj = ft_set_main_obj(fractal_id, argv, argc);
	if (fractal_id == MANDELBROT_ID)
		draw_mandelbrot(&main_obj);
	else if (fractal_id == JULIA_ID)
		draw_julia(&main_obj, main_obj.julia_real, main_obj.julia_imag);
	mlx_put_image_to_window(main_obj.mlx, main_obj.mlx_win, main_obj.image, 0, 0);
	mlx_mouse_hook(main_obj.mlx_win, zoom_hook, &(main_obj));
	mlx_key_hook(main_obj.mlx_win, buttons_tap_handler_hook, &(main_obj));
	mlx_hook(main_obj.mlx_win, 17, 0, close_cross_btn_tapped, &(main_obj));
	mlx_loop(main_obj.mlx);
	return (0);
}

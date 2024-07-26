/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_obj_init_ft.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:38:11 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/25 17:40:58 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	destroy_app(t_main_obj *obj, int exit_id)
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
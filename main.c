/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:45:13 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/15 15:58:00 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void destroy_app(void *p)
{
	main_obj *obj;

    obj = (main_obj *)p;
	mlx_destroy_image(obj->mlx, obj->image);
	mlx_destroy_window(obj->mlx, obj->mlx_win);
	mlx_destroy_display(obj->mlx);
	free(obj->mlx);
	exit(0);
}

int buttons_tap_handler_hook(int key, void *p) {
   
    main_obj *obj;

    obj = (main_obj *)p;
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

    draw_mandelbrot(obj->bpp1, obj->sl1, obj->endian1, obj->img_data, &(obj->math_num));
	mlx_put_image_to_window(obj->mlx, obj->mlx_win, obj->image, 0, 0);
    return 0;
}

int close_cross_btn_tapped(void *p) {
    destroy_app(p);
    return (0);
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

main_obj ft_set_main_obj() {
    main_obj main_obj;

    main_obj.mlx = mlx_init();
    main_obj.mlx_win = mlx_new_window(main_obj.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
    main_obj.image = mlx_new_image(main_obj.mlx, WIN_WIDTH, WIN_HEIGHT);
    main_obj.img_data = mlx_get_data_addr(main_obj.image, &(main_obj.bpp1), &(main_obj.sl1), &(main_obj.endian1));
    main_obj.math_num = init_limits();

    return main_obj;
}

int handle_input(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		write(1, "Wrong amount of param!\n", 23);
		write(1, "Mandatory parameters amount(2):\n, ", ft_strlen("Mandatory parameters: amount(2)\n"));
		write(1, "[mand/jul] | [sd]\n", 19);
	} else {

	}
	return (200);
}

int main(int argc, char **argv) {

    main_obj main_obj;

	handle_input(argc, argv);

    main_obj = ft_set_main_obj();
	if (argv)
    draw_mandelbrot(main_obj.bpp1, main_obj.sl1, main_obj.endian1, main_obj.img_data, &(main_obj.math_num));
    mlx_put_image_to_window(main_obj.mlx, main_obj.mlx_win, main_obj.image, 0, 0);
    mlx_mouse_hook(main_obj.mlx_win, zoom_hook, &(main_obj));
    mlx_key_hook(main_obj.mlx_win, buttons_tap_handler_hook, &(main_obj));

    mlx_hook(main_obj.mlx_win, 17, 0, close_cross_btn_tapped, &(main_obj));
    mlx_loop(main_obj.mlx);

    return 0;
}

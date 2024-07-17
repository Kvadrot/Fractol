/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:54:19 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 17:38:11 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_WIDTH 242
# define WIN_HEIGHT 242
# define ZOOM_STEP 1.2
# define MAX_ITER 100
# define MANDELBROT_ID 333
# define JULIA_ID 334
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct t_min_max
{
	double	min;
	double	max;
}	t_min_max;

typedef struct t_math_val
{
	double		x_offset;
	double		y_offset;
	t_min_max	real_num;
	t_min_max	imag_num;

}	t_math_val;

typedef struct t_main_obj
{
	int			fractal_id;
	void		*mlx;
	void		*mlx_win;
	void		*image;
	char		*img_data;
	int			bpp1;
	int			sl1;
	int			endian1;
	double		julia_real;
	double		julia_imag;
	t_math_val	math_num;
}	t_main_obj;

t_math_val	init_mandelbrot_limits(void);
int			mandelbrot(double real, double imag);
void		draw_mandelbrot(t_main_obj *obj);
void		draw_julia(t_main_obj *obj, double real_num, double complex_num);
int			drawhelper(t_main_obj *obj, int iter, int x, int y);
size_t		ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(const char *nptr);
int			ft_atod(char *str_num, double *save_to);

#endif
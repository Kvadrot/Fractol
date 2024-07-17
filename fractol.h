/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:54:19 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/16 17:22:12 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

#define WIN_WIDTH 242
#define WIN_HEIGHT 242
#define ZOOM_STEP 1.2
#define MAX_ITER 1000
#define MANDELBROT_ID 333
#define JULIA_ID 334

# include <unistd.h>
# include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

// typedef struct {
//     void *mlx;
//     void *mlx_win;
//     void *image;
//     char *img_data;
//     int bpp1;
//     int sl1;
//     int endian1;
//     math_val math_num;
// } main_obj;
typedef struct {
	int	fractal_id;
    void *mlx;
    void *mlx_win;
    void *image;
    char *img_data;
    int bpp1;
    int sl1;
    int endian1;
	double julia_real;
	double julia_imag;
    math_val math_num;
} main_obj;

math_val	init_mandelbrot_limits();
int			mandelbrot(double real, double imag);
void		draw_mandelbrot(int bpp1, int sl1, int endian1, char *data, math_val *math_val);

size_t		ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(const char *nptr);

#endif
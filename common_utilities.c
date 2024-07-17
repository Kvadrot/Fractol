/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:24:50 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 17:39:53 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
	{
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}

int	ft_atod(char *str_num, double *save_to)
{
	int		i;
	int		sign;
	double	integer_temp;
	double	fractinal_temp;

	sign = 1;
	i = 0;
	integer_temp = 0;
	fractinal_temp = 0;
	if (str_num[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str_num[i] >= '0' && str_num[i] <= '9')
	{
		integer_temp *= 10;
		integer_temp += str_num[i] - '0';
		i++;
	}
	if (str_num[i] == '.')
	{
		i++;
		while (str_num[i] >= '0' && str_num[i] <= '9')
		{
			fractinal_temp *= 10;
			fractinal_temp += str_num[i] - '0';
			i++;
		}
	}
	else
		return (404);
	while (fractinal_temp > 1)
		fractinal_temp /= 10;
	*save_to = (integer_temp + (fractinal_temp)) * sign;
	return (200);
}

int	drawhelper(t_main_obj *obj, int iter, int x, int y)
{
	int	color;
	int	brightness;
	int	pixel_index;

	if (iter == MAX_ITER)
		color = 0x000000;
	else
	{
		brightness = 255 * iter / MAX_ITER;
		color = (brightness << 16) + (brightness << 8) + brightness;
	}
	pixel_index = (y * obj->sl1) + (x * obj->bpp1 / 8);
	obj->img_data[pixel_index] = color;
	obj->img_data[pixel_index + 1] = (color >> 8);
	obj->img_data[pixel_index + 2] = (color >> 16);
}

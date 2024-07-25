/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:24:50 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/24 14:00:00 by itykhono         ###   ########.fr       */
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

void	ft_mini_atoi(char *str, int *i, double *temp)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*temp *= 10;
		*temp += str[*i] - '0';
		i += 1;
	}
	return ;
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


// int main()
// {
// 	double a = 0;

// 	ft_atod("-0.asda4qw QWTR 	2U32UHN34ON123YU841O24Y8 123437812 234918 9YB asdasd as", &a);
// 	printf("%f", a);
// }
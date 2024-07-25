/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:17:41 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/25 17:34:13 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "fractol.h"
#include "stdlib.h"
#include "stdio.h"

int	validate_jul_param(char *param)
{
	int	i;
	int	dots;

	dots = 0;
	i = 0;
	while (param[i] != '\0')
	{
		if (param[i] == '.')
		{
			dots++;
			i++;
		}
		if (('0' > param[i] || param[i] > '9'))
			return (401);
		i++;
	}
	i = 0;
	if (dots != 1)
		return (402);
	while (param[i] != '.')
		i++;
	if (i > 1 || i == 0)
		return (403);
	return (200);
}

static int	convert_after_dot(int *i, double *div, double *f_temp, char *str)
{
	(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*f_temp = *f_temp * 10 + (str[*i] - '0');
		*div *= 10;
		(*i)++;
	}
}

void	ft_atod(char *str_num, double *save_to)
{
	double	integer_temp;
	double	fractional_temp;
	double	divisor;
	int		i;
	int		sign;

	sign = 1;
	i = 0;
	integer_temp = 0;
	fractional_temp = 0;
	divisor = 1;
	if (str_num[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str_num[i] >= '0' && str_num[i] <= '9')
	{
		integer_temp = integer_temp * 10 + (str_num[i] - '0');
		i++;
	}
	if (str_num[i] == '.')
		convert_after_dot(&i, &divisor, &fractional_temp, str_num);
	*save_to = (integer_temp + (fractional_temp / divisor)) * sign;
}
/*
int main(void)
{
	char *str = "1.000102301203011230102.40140140";
	char *str1 = "1.22";
	char *str2 = "12.0310249409.22";
	char *str3 = "1203..10249409.22";
	char *str4 = "0.24.";
	char *str5 = "2.rr1";
	char *str6 = "0q.1244";
	char *str7 = "0.224141562457u3483948698346598346";
	char *str8 = "0a.22";
	char *str9 = "aasd.22";


	printf("str: %s = %d\n", str, validate_jul_param(str));
	printf("str1: %s = %d\n",str1, validate_jul_param(str1));
	printf("str: %s = %d\n", str2, validate_jul_param(str2));
	printf("str: %s = %d\n", str3, validate_jul_param(str3));
	printf("str: %s = %d\n", str4, validate_jul_param(str4));
	printf("str: %s = %d\n", str5, validate_jul_param(str5));
	printf("str: %s = %d\n", str6, validate_jul_param(str6));
	printf("str: %s = %d\n", str7, validate_jul_param(str7));
	printf("str: %s = %d\n", str8, validate_jul_param(str8));
	printf("str: %s = %d\n", str9, validate_jul_param(str9));
}*/
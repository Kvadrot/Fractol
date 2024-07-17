/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:24:50 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 10:56:53 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "fractol.h"
#include <stdio.h>

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
	while 	(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
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
			printf("%c",str_num[i]);
			fractinal_temp += ft_atoi(char *(str_num[i]));
			fractinal_temp /= 10;
			i++;
			printf("%f\n", fractinal_temp);
		}
	} else {
		return (404);
	}
	*save_to = integer_temp + (fractinal_temp);
	
	return (200);
}

int main()
{
	double a;
	a = 0;

	atod("2.2231", &a);
	printf("%f",a);
}
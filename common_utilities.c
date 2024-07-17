/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:24:50 by itykhono          #+#    #+#             */
/*   Updated: 2024/07/17 13:05:23 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "fractol.h"
#include <stdio.h>
#include <stdlib.h>


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

int	ft_atod(char *str_num, double *save_to)
{
	int i = 0;
	double integer_temp;
	double fractinal_temp;
	int sign;

	integer_temp = 0;
	fractinal_temp = 0;
	sign = 1;
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
	} else
		return (404);
	while (fractinal_temp > 1)
		fractinal_temp /= 10;
	*save_to = (integer_temp + (fractinal_temp)) * sign;
	return (200);
}

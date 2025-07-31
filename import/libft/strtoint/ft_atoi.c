/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:43:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/02/24 19:41:53 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strtoint.h"

long	ft_atoi(const char *str)
{
	long	number;
	int		kind;

	number = 0;
	kind = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		kind = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - 48;
		str++;
	}
	if (kind % 2 == 1 && number * (-1) >= INT_MIN)
		return (-number);
	else if (number <= INT_MAX)
		return (number);
	return (LONG_MAX);
}

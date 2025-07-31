/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:20:09 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 17:14:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(t_flags *flags, char ch)
{
	if (flags->zpad || flags->right)
	{
		ft_fill(flags->width, 1, ' ');
		ft_putchar_fd(ch, 1);
		return (flags->width);
	}
	else if (flags->left)
	{
		ft_putchar_fd(ch, 1);
		ft_fill(flags->width, 1, ' ');
		return (flags->width);
	}
	ft_putchar_fd(ch, 1);
	return (1);
}

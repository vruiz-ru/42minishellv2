/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:18:21 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 17:21:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nullcase(t_flags *flags)
{
	int	width;
	int	length;

	width = 0;
	length = 6;
	if ((flags->precw > 0 && flags->precw < 6) \
			|| (flags->prec && !flags->precw))
		length = 0;
	if (flags->zpad || (!flags->zpad && !flags->left && flags->width))
		width += ft_fill(flags->width, length, ' ');
	if (length == 0)
		width += write(1, "", 0);
	else
		width += write(1, "(null)", 6);
	if (flags->left)
		width += ft_fill(flags->width, length, ' ');
	return (width);
}

static int	ft_precstr(t_flags *flags, char *content)
{
	int	length;
	int	count;
	int	cut;

	length = ft_strlen(content);
	if (flags->precw >= length)
	{
		ft_putstr_fd(content, 1);
		return (length);
	}
	count = 0;
	cut = flags->precw;
	while (cut-- > 0)
	{
		ft_putchar_fd(*content++, 1);
		count++;
	}
	return (count);
}

int	ft_printstr(t_flags *flags, char *content)
{
	int	len;

	if (!content)
		return (ft_nullcase(flags));
	len = ft_strlen(content);
	if (flags->prec)
	{
		if (flags->precw > len)
			flags->precw = len;
		len = 0;
		if (flags->zpad || (!flags->zpad && !flags->left && flags->width))
			len = ft_fill(flags->width, flags->precw, ' ');
		len += ft_precstr(flags, content);
		if (flags->left)
			len += ft_fill(flags->width, flags->precw, ' ');
		return (len);
	}
	if (flags->zpad || flags->right)
		len += ft_fill(flags->width, len, ' ');
	ft_putstr_fd(content, 1);
	if (flags->left)
		len += ft_fill(flags->width, len, ' ');
	return (len);
}

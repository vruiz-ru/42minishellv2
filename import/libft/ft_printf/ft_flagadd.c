/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:36 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 18:22:28 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*ft_addright(va_list *args, t_flags *flags, const char *f)
{
	if ((ft_isdigit(*f) && *f != '0') || *f == '*')
	{
		flags->width = 0;
		if (*f == '*')
		{
			flags->width = va_arg(*args, int);
			f++;
		}
		while (ft_isdigit(*f))
		{
			flags->width = flags->width * 10 + (*f - '0');
			f++;
		}
		flags->right = 1;
	}
	return (f);
}

static const char	*ft_addleft(va_list *args, t_flags *flags, const char *f)
{
	char	tmp[2];

	tmp[0] = f[0];
	tmp[1] = '\0';
	if (*f == '-')
	{
        flags->width = 0;
		while (*f == '-')
		{
			f++;
			flags->left = 1;
		}
		if (*f == '*')
		{
			flags->width = va_arg(*args, int);
			f++;
		}
		while (ft_isdigit(*f))
		{
			flags->width = flags->width * 10 + (*f - '0');
			f++;
		}
		flags->zpad = 0;
	}
	return (f);
}

static const char	*ft_addzero(va_list *args, t_flags *flags, const char *f)
{
	if (*f == '0')
	{
		f++;
        flags->width = 0;
		if (*f == '*')
		{
			flags->width = va_arg(*args, int);
			f++;
		}
		else
		{
			while (ft_isdigit(*f))
			{
				flags->width = flags->width * 10 + (*f - '0');
				f++;
			}
		}
		flags->zpad = 1;
	}
	return (f);
}

static const char	*ft_addprec(va_list *args, t_flags *flags, const char *f)
{
	if (*f == '.')
	{
		f++;
		if (*f == '*' && !flags->prec)
		{
			flags->precw = va_arg(*args, int);
			f++;
		}
		while (ft_isdigit(*f) != 0)
		{
			flags->precw = flags->precw * 10 + (*f - '0');
			f++;
		}
		flags->prec = 1;
	}
	return (f);
}

const char	*ft_flagadd(va_list *args, t_flags *flags, const char *format)
{
	while (ft_strchr("# +", *format))
	{
		if (*format == '#')
			flags->alt = 2;
		else if (*format == '+')
		{
			flags->sign = 1;
			flags->space = 0;
		}
		else if (*format == ' ')
		{
			if (flags->sign == 1)
				flags->space = 0;
			else
				flags->space = 1;
		}
		format++;
	}
	format = ft_addleft(args, flags, format);
	format = ft_addzero(args, flags, format);
	format = ft_addright(args, flags, format);
	format = ft_addprec(args, flags, format);
	return (format);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:17:27 by aghergut          #+#    #+#             */
/*   Updated: 2024/10/16 16:11:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	if (!str)
		return ;
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}

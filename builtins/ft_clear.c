/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:37:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 13:40:13 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_clear(t_process *process, t_cmd *cmd)
{
    (void)process;
	(void)cmd;
	ft_printf("%s", CLEAR);
    return (1);
}

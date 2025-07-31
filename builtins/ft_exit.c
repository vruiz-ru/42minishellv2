/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:50:12 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 20:07:17 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_utils *main_struct)
{
	free_main(main_struct);
	rl_clear_history();
	exit(EXIT_SUCCESS);
	return (1);	
}
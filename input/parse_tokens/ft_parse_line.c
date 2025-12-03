/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 22:41:47 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

static int	is_sep_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	get_new_len(char *line, int i, int q)
{
	int	len;

	len = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && q != 2)
			q ^= 1;
		if (line[i] == '"' && q != 1)
			q ^= 2;
		if (!q && is_sep_char(line[i]))
		{
			len += 2;
			if (line[i + 1] == line[i] && line[i] != '|')
			{
				len++;
				i++;
			}
		}
		len++;
	}
	return (len);
}

static void	fill_line(char *new, char *line, int i, int j)
{
	int	q;

	q = 0;
	while (line[i])
	{
		if (line[i] == '\'' && q != 2)
			q ^= 1;
		if (line[i] == '"' && q != 1)
			q ^= 2;
		if (!q && is_sep_char(line[i]))
		{
			new[j++] = ' ';
			new[j++] = line[i];
			if (line[i + 1] == line[i] && line[i] != '|')
				new[j++] = line[++i];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i];
		i++;
	}
	new[j] = '\0';
}

static char	*format_line(char *line)
{
	char	*new;
	int		len;

	len = get_new_len(line, -1, 0);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	fill_line(new, line, 0, 0);
	return (new);
}

int	ft_parse_line(t_process *process)
{
	char	*cmd;
	char	*fmt;

	if (contains_variable(process->line))
		if (!ft_inputvar(process, &process->line))
			return (ft_clear_strtok(), 0);
	fmt = format_line(process->line);
	if (!fmt)
		return (perror("malloc"), ft_clear_strtok(), 0);
	free(process->line);
	process->line = fmt;
	cmd = ft_strtok(process->line, " ");
	ft_safeadd_tokens(&process->tokens, &cmd);
	if (!ft_strchr(process->line, ' '))
		return (ft_clear_strtok(), 1);
	if (!ft_std(process, process->line) && !ft_quote(process, process->line))
		return (ft_clear_strtok(), 0);
	return (ft_clear_strtok(), 1);
}

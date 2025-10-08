/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:19:55 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/08 14:42:36 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// quotes
void	pos_aux(char **str, int *idx, int *slash)
{
	while ((*str)[*idx] == '\\')
	{
		(*slash)++;
		(*idx)++;
	}   
}
// quotes
int	quote_pos(char *str, char delim, int times)
{
	int	idx;
	int	occurrence;
	int quote_idx;
	int slash;
	
	quote_idx = -1;
	idx = 0;
	occurrence = 0;
	while (str[idx])
	{
		slash = 0;
		pos_aux(&str, &idx, &slash);
		if (!str[idx])
			break;
		if (str[idx] == delim && (str[idx - 1] != '\\' || slash % 2 == 0))
		{
			occurrence++;
			quote_idx = idx;
		}
		if (occurrence == times)
			break;
		idx++;
	}
	return (quote_idx);
}
// quotes
int quotes_left(t_list *tokens, char *line_left)
{
	char    *space;
	char    *temp;
	
	if (!line_left || !*line_left)
		return (0);
	if (ft_strchr(line_left, '\'') || ft_strchr(line_left, '"'))
		return (1);
	if (line_left && *line_left == ' ')
	{
		space = ft_strdup(" ");
		temp = ft_strdup(line_left + 1);
		if (!space || !temp)
			return (perror("malloc"), 0);
		ft_lstadd_back(&tokens, ft_lstnew(space));
		ft_lstadd_back(&tokens, ft_lstnew(temp));
	}
	else
	{
		temp = ft_strdup(line_left + 1);
		if (!temp)
			return (perror("malloc"), 0);
		ft_lstadd_back(&tokens, ft_lstnew(temp));
	}
	return (0);
}
// quotes
int first_occurrence(t_list *tokens, char *line, char delim)
{
	char	*chunk;
	int 	idx;

	idx = quote_pos(line, delim, 1);
	if (idx < 0)
		return (-1);
	if (idx > 0)
	{
		chunk = ft_substr(line, 0, idx);
		if (!chunk)
			return(perror("malloc"), 0);
		ft_lstadd_back(&tokens, ft_lstnew(chunk));
	}
	return (idx);
}
// parse token
void	assign_value(char **env, char **dest, char *var_name)
{
	char	*value;
	int		idx;
	int		size;
	
	idx = 0;
	while (env[idx])
	{
		size = ft_strchr(env[idx], '=') - env[idx];
		if (!ft_strncmp(env[idx], var_name, size) && env[idx][size] == '=')
		{
			value = ft_strdup(ft_strchr(env[idx], '=') + 1);
			*dest = ft_strjoin_free(*dest, value);
			break ;
		}
		idx++;
	}
}
// parse token
int	is_within(char **env, char *var_name)
{
	int	idx;
	int size;
	
	idx = 0;
	while (env[idx])
	{
		size = ft_strchr(env[idx], '=') - env[idx];
		if (!ft_strncmp(env[idx], var_name, size))
			return (1);
		idx++;
	}
	return (0);
}
// parse token
char	*clean_line(char *content)
{
	char	*new;
	int		i;
	
	i = 0;
	new = NULL;
	if (!content || !*content)
		return (NULL);
	while (content[i] != '\0')
	{
		if (content[i] == '\\' && ft_strchr("\\`\"", content[i + 1]))
			i++;
		new = ft_addchar(new, content[i]);
		i++;
	}
	return (new);
}
// parse token
void scan_char(char *content, char **var_name, int *idx)
{
	char    *stop;

	stop = " \t\n/.,:-+=?!@#^&*()[]{}'\"\\|<>;~";
	if (content[*idx] == '\\' && content[*idx + 1] == '$')
	{
		(*idx)++;
		return ;
	}
	if (content[*idx] == '$')
	{
		(*idx)++;
		while (content[*idx] != '\0' && !ft_strchr(stop, content[*idx]))
		{
			*var_name = ft_addchar(*var_name, content[*idx]);
			(*idx)++;
		}	
	}
	return ;
}
// parse token
void	insert_value(t_subproc *process, char **dest, char *var_name)
{
	char	**local_env;
	char	**buffer_env;

	local_env = process->local_env;
	buffer_env = process->buffer_env;
	if (is_within(local_env, var_name))
		assign_value(local_env, dest, var_name);
	else if (is_within(buffer_env, var_name))
		assign_value(buffer_env, dest, var_name);
}
// parse token
char	*parse_token(t_subproc *process, char *content)
{
	char	*res;
	char	*var_name;
	int		i;

	i = 0;
	content = clean_line(content);
	res = NULL;
	while (content[i] != '\0')
	{
		var_name = NULL;
		scan_char(content, &var_name, &i);
		if (var_name != NULL)
		{
			insert_value(process, &res, var_name);
			if (!res)
				return (NULL);
		}
		res = ft_addchar(res, content[i]);
		i++;
	}
	return (res);	
}
// quotes
int reconstruct_token(t_subproc *process, char *line, char delim)
{
	t_list	**tokens;
	char	*res;
	int		start_idx;
	int		end_idx;

	tokens = &process->builtins->tokens;
	start_idx = first_occurrence(*tokens, line, delim);
	if (start_idx < 0)
		return (-1);
	end_idx = quote_pos(line, delim, 2);
	res = ft_substr(line, start_idx + 1, end_idx - (start_idx + 1));
	if (!res)
		return (perror("malloc"), 0);
	if (delim == '"')
		res = parse_token(process, res);
	ft_lstadd_back(tokens, ft_lstnew(res));
	return (1);
}
// quotes
char	*ft_quotes(t_subproc *process, char *line, char delim)
{
	char	*line_left;
	int		indexes_left;
	int		last_index;
	int		paired_delim;
	
	ft_printf("quotes1\n");
	line_left = NULL;
	indexes_left = 0;
	if (reconstruct_token(process, line, delim) < 0)
		return (NULL);
	ft_printf("quotes2\n");
	last_index = ft_strlen(line) - 1;
	paired_delim = quote_pos(line, delim, 2);
	if (paired_delim < last_index)
		indexes_left = last_index - paired_delim;
	if (indexes_left > 0)
	{
		line_left = ft_substr(line, paired_delim + 1, indexes_left);
		if (!line_left)
			return (perror("malloc"), NULL);
		ft_printf("quotes3\n");
	}
	free(line);
	ft_printf("quotes4\n");
	if (quotes_left(process->builtins->tokens, line_left))
		return (line_left);
	ft_printf("quotes5\n");
	free(line_left);
	return (NULL);
}

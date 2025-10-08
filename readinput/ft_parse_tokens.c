/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:53:45 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/08 14:33:43 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* funcs
int	ft_wildcards(char *str, char *wildcards)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(wildcards, str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_cleanline(char *content)
{
	char	*new;
	int		i;
	
	i = 0;
	new = NULL;
	if (!content || !*content)
		return (NULL);
	while (content[i] != '\0')
	{
		if (content[i] == '\\' && ft_strchr("\\`$\"", content[i + 1]))
			i++;
		new = ft_addchar(new, content[i]);
		i++;
	}
	return (new);
}

void	ft_addvalue(char **env, char **dest, char *var_name)
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

int	ft_within(char **env, char *var_name)
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

void	ft_scanning_quotes(char *content, char **new, int *idx)
{
	if (content[*idx] == '\'' && (*idx - 1) > 0 && content[*idx - 1] == '\\')
	{
		*new = ft_addchar(*new, content[*idx]);
		(*idx)++;
	}
	else if (content[*idx] == '\'')
		(*idx)++;
}	

void	ft_scanning_variable(char *content, char **var_name, int *idx)
{
	if ((content [*idx] == '$' && content[*idx - 1] != '\\') || \
		(content[*idx] == '"' && content[*idx - 1] != '\\' && \
		content[++(*idx)] == '$' && content[*idx - 1] != '\\'))
	{
		while (content[++(*idx)] != '\0' && \
			(content[*idx] != '"' && content[*idx] != ' '))
			{
				// ft_printf("prima iterare if/while scanvar\n");
				*var_name = ft_addchar(*var_name, content[*idx]);
				// ft_printf("var_name -->> %s\n", *var_name);
			}
		++(*idx);
	}
}

char	*ft_build_line(t_subproc *process, char *content)
{
	char    *new;
	char    *var_name;
	int     i;

	if (!content)
		return (NULL);
	i = 0;
	content = ft_cleanline(content);
	new = NULL;
	while (content[i] != '\0')
	{
		var_name = NULL;
		ft_scanning_variable(content, &var_name, &i);
		if (var_name != NULL)
		{
			ft_insert(process, &new, var_name);
			if (!new)
				return (NULL);
		}
		ft_scanning_quotes(content, &new, &i);
		new = ft_addchar(new, content[i]);
		i++;
	}
	return (new);
}

int	ft_parse_tokens(t_subproc *process)
{
	t_list	*tokens;
	t_list  *temp;
	char    *content;
	char	*new_line;

	tokens = process->builtins->tokens->next;
	new_line = NULL;
	while (tokens)
	{
		content = tokens->content;
		if (ft_wildcards(content, "\\\"'$"))
			new_line = ft_strjoin_free(new_line, ft_build_line(process, content));
		else if (new_line == NULL)
			new_line = ft_strdup(content);
		else
			new_line = ft_strjoin_free(new_line, content);
		temp = tokens->next;
		free(tokens);
		tokens = temp;
	}
	process->builtins->tokens->next = NULL;
	ft_lstadd_back(&process->builtins->tokens, ft_lstnew(new_line));
	return (1);
}
*/

/* CLEANLINE PROTOTYPE
char	*ft_cleanline(char *content)
{
	char    *new;
	int		legit;
	int     i;

	i = 0;
	new = NULL;
	if (!content || !*content)
		return (NULL);
	while (content[i] != '\0')
	{
		legit = 0;
		while (content[i] == '\\')
		{
			legit++;
			if (legit % 2 == 0)
				new = ft_addchar(new, content[i]);
			i++;
		}
		if (legit % 2 == 1)
			i--;
		if (content[i] != '\0')
			new = ft_addchar(new, content[i]);
		i++;
	}
	return (free(content), new);
}
*/
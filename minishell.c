#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#define PROMPT_ARROW	" 👉 "
#define PROMPT_HOME		"minishell:~ 👉 "
#define HOME	"~"
#define REPLY	"💬"
#define WRONG	"❓"
#define NAME	"minishell42"
#define CLEAR	"\e[1;1H\e[2J"	// \033[H\033[J

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct Environment_utils
{
	char	**parent_env;
	char	**static_env;
}	t_envs;

typedef struct Prompt_utils
{
	char	*display;
	char	*shell_name;
	char	*home_path;
	char	*current_wd;
	char	*last_wd;
}	t_prompt;

typedef struct Process_utils
{
	t_prompt	*prompt;
	t_envs		*envs;
	t_list		*tokens;
	pid_t		pid;
	char		*line;
	char		*last_arg;
	int			exit_status;
	bool		is_special;
    bool        is_variable;
}   t_process;

typedef struct Process_utils t_process;

void	ft_setpaths(t_process *process);
int     ft_pwd(t_process *process);
char	*ft_getcwd(void);
char	*parse_token(t_process *process, char *content, char token);

// LIBFT USED FUNCTIONS

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cast;
	size_t			i;

	cast = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		cast[i] = 0;
		i++;
	}
	s = cast;
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') \
			|| (c >= 'A' && c <= 'Z') \
			|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*str;

	str = malloc(n * size);
	if (str)
	{
		ft_bzero(str, n * size);
		return (str);
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (0);
	while (i < ft_strlen(s))
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;
	int		i;
	int		j;	

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		res = (char *) malloc((len + 1) * sizeof(char));
		if (res == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			res[i] = s1[i];
		j = 0;
		while (s2[j])
			res[i++] = s2[j++];
		res[i] = '\0';
		return (res);
	}
	return (0);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	size_t	i;
	size_t	join_i;
	char	*join;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		join = ft_substr(s2, 0, ft_strlen(s2));
		if (!join)
			return (free((void *)s2), s2 = NULL, NULL);
		return (free((void *)s2), s2 = NULL, join);
	}
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) +1) * sizeof(char));
	if (!join)
		return (free((void *)s1), free((void *)s2), NULL);
	join_i = -1;
	while (s1[++join_i] != '\0')
		join[join_i] = s1[join_i];
	i = 0;
	while (s2[i] != '\0')
		join[join_i++] = s2[i++];
	join[join_i] = '\0';
	return (free((void *)s1), s1 = NULL, free((void *)s2), s2 = NULL, join);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;
	size_t			i;

	if (n == 0 || !s1 || !s2)
		return (0);
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (i < n && cs1[i] == cs2[i] && cs1[i] != '\0')
		i++;
	if (i == n)
		return (0);
	return (cs1[i] - cs2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *str, int ch)
{
	char	c;

	if (!str)
		return (NULL);
	c = ch;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}

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

static int	v_length(long value)
{
	int	len;

	if (value < INT_MIN || value > INT_MAX)
		return (0);
	len = 1;
	if (value < 10)
		return (len);
	if (value < 0)
		value *= -1;
	while (value > 9)
	{
		value /= 10;
		len++;
	}
	return (len);
}

static char	*v_str(int len, int value, int kind)
{
	char	*number;

	if (kind == 0)
		number = ft_calloc((len + 2), sizeof(char));
	else
	{
		number = ft_calloc((len + 1), sizeof(char));
		len--;
	}
	if (!number)
		return (0);
	while (len >= 0)
	{
		if (len == 0 && kind == 0)
		{
			number[len] = '-';
			return (number);
		}
		number[len] = (value % 10) + '0';
		value /= 10;
		len--;
	}
	return (number);
}

char	*ft_itoa(long value)
{
	if (!v_length(value))
		return (NULL);
	if (value == -2147483648)
		return (ft_strdup("-2147483648"));
	if (value < 0)
	{
		value *= -1;
		return (v_str(v_length(value), value, 0));
	}
	return (v_str(v_length(value), value, 1));
}

static char	*failed_malloc(void)
{
	write(1, "Failed malloc!\n", sizeof("Failed malloc!\n") - 1);
	return (NULL);
}

static char	*get_token(char *cpy, const char *delim)
{
	char	*token;
	int		size;
	int		i;

	if (!cpy || !*cpy)
		return (NULL);
	while (*cpy && cpy && ft_strchr(delim, *cpy))
		cpy++;
	if (!*cpy)
		return (NULL);
	size = 0;
	while (cpy[size] && !ft_strchr(delim, cpy[size]))
		size++;
	token = malloc((size + 1) * sizeof(char));
	if (!token)
		return (failed_malloc());
	i = -1;
	while (++i < size)
		token[i] = cpy[i];
	token[i] = '\0';
	return (token);
}

static char	*trim_static(char *cpy, const char *delim)
{
	char	*new;
	int		size;
	int		i;

	size = 0;
	while (cpy[size] && ft_strchr(delim, cpy[size]))	// skip leading delim
		size++;
	while (cpy[size] && !ft_strchr(delim, cpy[size]))	// skip last token
		size++;
	while (cpy[size] && ft_strchr(delim, cpy[size]))	// skip delim 
		size++;
	if (!cpy[size])
		return (free(cpy), NULL);
	new = malloc((ft_strlen(cpy + size) + 1) * sizeof(char));		
	if (!new)
		return (failed_malloc());
	i = 0;
	while (cpy[size])
		new[i++] = cpy[size++];
	new[i] = '\0';
	free(cpy);
	return (new);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char *cpy = NULL;
	char		*token;

	if (str == NULL && cpy == NULL)
		return (NULL);
	if (delim == NULL || !*delim)
		return (NULL);
	if (str)
	{
		free(cpy);
		cpy = ft_strdup(str);
		if (!cpy)
			return (failed_malloc());
	}
	token = get_token(cpy, delim);
	cpy = trim_static(cpy, delim);
	return (token);
}

char	*ft_addchar(char *str, char ch)
{
	char	*new;
	size_t	new_size;
	size_t	i;

	if (!str || !*str)
		new_size = 1;
	else
		new_size = ft_strlen(str) + 1;
	new = malloc((new_size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (str && str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = ch;
	new[i] = '\0';
	if (str)
		free(str);
	str = NULL;
	return (new);	
}

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*c_str;
	size_t			i;

	c_str = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		c_str[i] = (unsigned char)c;
		i++;
	}
	return (str = c_str);
}

// LISTS FUNCTIONS

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del && lst->content)
			del(lst->content);
		free(lst);
		lst = NULL;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
	}
	lst = temp;
	return (lst);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *) malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (content)
	{
		node->content = content;
		node->next = NULL;
		return (node);
	}
	return (free(node), NULL);
}

size_t	ft_lstsize(t_list *lst)
{
	size_t	count;

	if (lst)
	{
		count = 0;
		while (lst != NULL)
		{
			count++;
			lst = lst->next;
		}
		return (count);
	}
	return (0);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	if (lst)
	{
		ptr = *lst;
		while (ptr != NULL)
		{
			temp = ptr->next;
			ft_lstdelone(ptr, del);
			ptr = temp;
		}
		*lst = NULL;
	}
}

// MAPS FUNCTIONS
void	free_partial(char **map, size_t count)
{
	if (!map)
		return;
	while (count >= 0)
	{
		count--;
		free(map[count]);
	}
	free(map);
}

char	**create_new(char **map, char *add_last)
{
	char    **new_map;
	int		i;

	new_map = malloc((ft_mapsize(map) + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return (free_partial(new_map, i), NULL);
		i++;
	}
	new_map[i] = ft_strdup(add_last);
	if (new_map[i] == NULL)
		return (free_partial(new_map, i), NULL);
	new_map[i + 1] = NULL;
	return (new_map);
}

int	copy_elements(char **map, char **new_map, size_t skip)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		if (i == skip)
		{
			i++;
			continue;
		}
		new_map[j] = ft_strdup(map[i]);
		if (!new_map[j])
		{
			free_partial(new_map, j);
			return (0);
		}
		j++;
		i++;
	}
	new_map[j] = NULL;
	return (1);
}

int	right_length(char *item)
{
	char	*ptr;
	
	ptr = ft_strchr(item, '=');
	if (ptr)
		return (ptr - item);
	return (ft_strlen(item));
}

char	**ft_mapdup(char **map)
{
	char	**dup;
	size_t	length;
	int		i;

	length = ft_mapsize(map);
	if (!length)
		return (NULL);
	dup = (char **)malloc((length + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (map[i])
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
            return (free_partial(dup, i), NULL);
        i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	ft_mapfree(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
    {
        free(map[i]);
        i++;
    }
	free(map);
}


int	ft_mapitem_add(char ***map_ref, char *item)
{
	char	**map;
	char	**new;

	if (!map_ref)
		return (0);
	map = *map_ref;
	if (map == NULL)
	{
		*map_ref = ft_mapnew(item);
		if (*map_ref == NULL)
			return (0);
		return (1);
	}
	new = create_new(map, item);
	if (new != NULL)
	{
		ft_mapfree(map);
		*map_ref = new;
		return (1);	
	}
	return (0);
}

int	ft_mapitem_del(char ***map_ref, size_t del_idx)
{
	char	**new_map;
	char	**temp;
	size_t	length;

	if (!map_ref || !*map_ref)
		return (0);
	temp = *map_ref;
	length = ft_mapsize(temp);
	if (del_idx >= length)
		return (0);
	new_map = (char **)malloc(length * sizeof(char *));
	if (!new_map)
		return (0);
	if (!copy_elements(temp, new_map, del_idx))
		return (ft_mapfree(new_map), 0);
	ft_mapfree(temp);
	*map_ref = new_map;
	return (1);
}


int  ft_mapitem_index(char **map, char *str)
{
	size_t  mv_len;
	size_t	sv_len;
	size_t  idx;
	
	if (!map || !*map || !str || !*str)
		return (-1);
	sv_len = right_length(str);
	idx = 0;
	while (map[idx])
	{
		mv_len = right_length(map[idx]);
		if (mv_len == sv_len && !ft_strncmp(map[idx], str, mv_len))
			return (idx);
		idx++;
	}
	return (-1);
}

int	ft_mapitem_replace(char ***map, char *item, size_t idx)
{
	char    *temp;
	
	if (!map || !*map || ft_mapsize(*map) <= idx)
		return (0);
	temp = ft_strdup(item);
	if (!temp)
		return (0);
	if ((*map)[idx])
		free((*map)[idx]);
	(*map)[idx] = temp;
	return (1);
}

char	**ft_mapnew(char *item)
{
	char	**map;

	if (!item)
		return (NULL);
	map = malloc(2 * sizeof(char *));
	if (!map)
		return (NULL);
	map[0] = ft_strdup(item);
	if (!map[0])
		return (free(map), NULL);
	map[1] = NULL;
	return (map);
}


size_t	ft_mapsize(char **map)
{
	size_t	i;
	
	i = 0;
	if (!map || !*map)
		return (0);
	while (map[i] != NULL)
		i++;
	return (i);
}


// UTILS

void	ft_addspace(t_list **tokens)
{
	char	*to_add;

	if (*tokens == NULL)
		return ;
	to_add = ft_strdup(" ");
	if (!to_add)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(tokens, ft_lstnew(to_add));
}

void	ft_clear_strtok(void)
{
	char	*buffer;

	buffer = ft_strtok(NULL, " ");
	if (!buffer)
		return ;
	while (buffer)
	{
		free(buffer);
		buffer = ft_strtok(NULL, " ");
	}
	return ;
}

static int	static_variable(char *str)
{
	if (ft_strchr(str, '='))
		return (1);
	return (0);	
}

static char	*copy_content(char *dst, char *src)
{
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dst = ft_addchar(dst, src[i]);
		if (dst == NULL)
			return (NULL);
		i++;
	}
	return (dst);
}

char	*ft_construct(t_list *tokens, char *str)
{
	t_list	*args;
	char	*content;

	args = tokens;
	if (!static_variable(str))
		args = args->next;
	if (str)
		free(str);
	str = NULL;
	while (args)
	{
		content = (char *)args->content;
		str = copy_content(str, content);
		args = args->next;
	}
	return (str);
}

void	free_process(t_process *proc)
{
	if (proc->envs && proc->envs->parent_env)
		free(proc->envs->parent_env);
	if (proc->envs && proc->envs->static_env)
		free(proc->envs->static_env);
	if (proc->envs)
		free(proc->envs);
	if (proc->prompt && proc->prompt->shell_name)
		free(proc->prompt->shell_name);
	if (proc->prompt && proc->prompt->display)
		free(proc->prompt->display);
	if (proc->prompt && proc->prompt->home_path)
		free(proc->prompt->home_path);
	if (proc->prompt && proc->prompt->current_wd)
		free(proc->prompt->current_wd);
	if (proc->prompt && proc->prompt->last_wd)
		free(proc->prompt->last_wd);
	if (proc->prompt)
		free(proc->prompt);
	if (proc->line)
		free(proc->line);
	if (proc->tokens)
		ft_lstclear(&proc->tokens, free);
	if (proc->last_arg)
		free(proc->last_arg);
}

static t_process	*init(void)
{
	t_process	*process;
	
	process = malloc(sizeof(t_process));
	if (!process)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	ft_memset(process, 0, sizeof(t_process));
	process->envs = malloc(sizeof(t_envs));
	process->prompt = malloc(sizeof(t_prompt));
	if (!process->envs && !process->prompt)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	ft_memset(process->envs, 0, sizeof(t_envs));
	ft_memset(process->prompt, 0, sizeof(t_envs));
	return (process);
}

t_process	*init_child(t_process *parent)
{
	t_process	*child;
	
	child = init();
	if (!child)
		return (NULL);
	child->envs->parent_env = ft_mapdup(parent->envs->parent_env);
	if (!child->envs->parent_env)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	child->prompt->current_wd = ft_strdup(parent->prompt->current_wd);
	if (!child->prompt->current_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	child->prompt->last_wd = ft_strdup(child->prompt->current_wd);
	if (!child->prompt->last_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	child->last_arg = ft_strdup(" ");
	if (!child->last_arg)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	child->pid = getpid();
	return (child);
}

int	init_parent(t_process **parent, char *name, char *envp[])
{
	*parent = init();
	if (!*parent)
		return (0);
	(*parent)->envs->parent_env = ft_mapdup(envp);
	if (!(*parent)->envs->parent_env)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->shell_name = ft_strdup(name);
	if (!(*parent)->prompt->shell_name)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->home_path = ft_getcwd();
	if (!(*parent)->prompt->home_path)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->current_wd = ft_getcwd();
	if (!(*parent)->prompt->current_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->last_wd = ft_getcwd();
	if (!(*parent)->prompt->last_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->pid  = getpid();
	(*parent)->last_arg = ft_strdup(" ");
	if (!(*parent)->last_arg)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	return (1);
}

// HANDLER CTRL+C

void	handle_sigint(int sig) 
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();	
	}
}

// BUILTINS UTILS FUNCTIONS

int	dash_feature(t_process *process)
{
	t_list	*token_feat;
	char	*path;

	token_feat = process->tokens->next;
	if (!token_feat->next)
	{
		if (chdir(process->prompt->home_path) != 0)
			return (perror("cd error"), 0);
		ft_setpaths(process);
		if (!process->prompt->last_wd || !process->prompt->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
		return (1);
	}
	path = (char *)token_feat->next->content;
	if (chdir(path) != 0)
		printf("cd: %s: No such file or directory\n", path);
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (1);
}

int	up_feature(t_process *process)
{
	char	*token;
	char	*path;
	int		size;
	
	size = ft_strlen(process->prompt->current_wd);
	if (!ft_strncmp(process->prompt->current_wd, process->prompt->home_path, size))
		return (1);
	path = (char *)process->tokens->next->content;
	token = ft_strtok(path, "/");
	while (token)
	{
		if (!ft_strncmp(token, "--", ft_strlen(token)))
			return(free(token), dash_feature(process));
		if (chdir(token) != 0)
		{
			printf("cd: %s: No such file or directory\n", path);
			return (free(token), 1);
		}
		free(token);
		token = ft_strtok(NULL, "/");
	}
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (1);
}

int	home_feature(t_process *process)
{
	char	*token_path;
	char	*home_path;
	char	*path;
	int		only_char;

	token_path = (char *)process->tokens->next->content;
	home_path = process->prompt->home_path;
	only_char = 0;
	if (token_path[0] == '~' && !token_path[1])
		only_char = 1;
	if (only_char)
		path = ft_strdup(home_path);
	else
		path = ft_strjoin(home_path, token_path + 1);
	if (chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", token_path);
		return (free(path), 1);
	}	
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (free(path), ft_putstr_fd("Malloc failed\n", 1), 0);
	return(free(path), 1);
}

int	back_feature(t_process *process)
{
	char	*last_wd;

	last_wd = process->prompt->last_wd;
	if (chdir(last_wd) != 0)
	{
		printf("cd: %s: No such file or directory\n", last_wd);
		return (1);
	}
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (ft_pwd(process));
}

int	root_feature(t_process *process)
{
	char	*home_path;
	char	*path;

	if (ft_lstsize(process->tokens) > 2)
		return (ft_putstr_fd("cd: Too many arguments\n", 1), 1);
	home_path = process->prompt->home_path;
	path = (char *)process->tokens->next->content;
	if (chdir(path) == 0)
	{
		ft_putstr_fd("cd: root: Permission denied\n", 1);
		ft_putstr_fd("cd: Moving to home folder\n", 1);
		if (chdir(home_path) != 0)
			return (perror("cd error"), 0);
		ft_setpaths(process);
		if (!process->prompt->last_wd || !process->prompt->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
	}
	else
		printf("cd: %s: No such file or directory\n", path);
	return (1);
}

void	ft_setpaths(t_process *process)
{
	char	**last_wd;
	char	**current_wd;

	last_wd = &process->prompt->last_wd;
	current_wd = &process->prompt->current_wd;
	if (*last_wd)
		free(*last_wd);
	*last_wd = ft_strdup(*current_wd);
	if (!*last_wd)
		return ;
	free(*current_wd);
	*current_wd = ft_getcwd();
}

int	invalid_options(char *token)
{
	int		idx;
	int		count;
	
	count = 0;
	idx = 0;
	while (token[idx])
	{
		if (count > 2 && idx == count)
			return (1);
		if (token[idx] == '-')
			count++;
		idx++;
	}
	return (0);
} 

int path_input(t_process *process)
{
	t_list	*ptr;
	char	*path;

	ptr = process->tokens->next;
	path = (char *)ptr->content;
	if (ft_isalnum(path[0]))
	{
		if (ptr->next)
			return (ft_putstr_fd("cd: too many arguments\n", 1) ,1);
		if (chdir(path) != 0)
		{
			printf("cd: %s: No such file or directory\n", path);
			return (1);
		}
		ft_setpaths(process);
		if (!process->prompt->last_wd || !process->prompt->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
		return (1);
	}
	return (0);
}

char	*ft_getcwd(void)
{
	char	cwd[4096];
	char	*res;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("getcwd"), exit(EXIT_FAILURE), NULL);
	res = ft_strdup(cwd);
	if (!res)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (res);
}


char	*ft_getvar(char **envp, char *var_name)
{
	char	*value;
	int		name_length;
	int		i;

	i = 0;
	value = NULL;
	while (envp[i])
	{
		name_length = ft_strchr(envp[i], '=') - envp[i];
		if (!ft_strncmp(envp[i], var_name, name_length))
		{
			if (envp[i][name_length + 2])
			{
				value = ft_strdup(envp[i] + name_length + 2);
				if (!value)
					return (perror("malloc"), exit(EXIT_FAILURE), NULL);
			}
			else
				break ;
			return (value);
		}
		i++;
	}
	return (NULL);
}

// BUILTINS FUNCTIONS

static int  ft_home(t_process *process)
{
	char    *home_path;

	home_path = process->prompt->home_path;
	if (chdir(home_path) != 0)
		ft_putstr_fd("cd: Failed returning to home path!", 1);
	ft_setpaths(process);
	return (1);
}

int ft_cd(t_process *process)
{
	t_list	*ptr;
	char	*feature;
	int		size;

    ptr = process->tokens->next;
	if (ptr == NULL)
		return(ft_home(process));
	feature = (char *)ptr->content;
	size = ft_strlen(feature);
	if (invalid_options(feature))
		return (ft_putstr_fd("cd: invalid options\n", 1), 1);
	if (path_input(process))
		return (1);
	if (!ft_strncmp(feature, "..", size) || ft_strnstr(feature, "../", 3))
		return (up_feature(process));
	if (ft_strnstr(feature, "~/", 2) || feature[0] == '~')
		return (home_feature(process));
	if (!ft_strncmp("-", feature, size))
		return (back_feature(process));
	if (feature[0] == '/')
		return (root_feature(process));
	if (!ft_strncmp("--", feature, size))
		return (dash_feature(process));
	return (1);
}

void	ft_clear(void)
{
	ft_printf("%s", CLEAR);
}

int	ft_echo(t_process *process)
{
	char	*res;
	
	res = NULL;
    res = ft_construct(process->tokens, res);
	ft_printf("%s\n",res);
	return (free(res), 1);
}

int	ft_exit(t_process *process)
{
	free_process(process);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	process->exit_status = 0;
	exit(EXIT_SUCCESS);
	return (1);
}


static void	update(char ***map, char *var)
{
	int 	env_idx;
	
	env_idx = ft_mapitem_index(*map, var);
	if (env_idx < 0)
		return ;
	if (!ft_mapitem_replace(map, var, env_idx))
		return ;
	return ;
}

static void	transfer(t_process *process, char *var)
{
	char	*get_var;
	int		idx;
	
	idx = ft_mapitem_index(process->envs->static_env, var);
	if (idx < 0)
		return ;
	get_var = ft_strdup(process->envs->static_env[idx]);
	if (!get_var)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (!ft_mapitem_add(&process->envs->parent_env, get_var))
	{
		free(get_var);
		return ;
	}
	ft_mapitem_del(&process->envs->static_env, idx);
	free(get_var);
	return ;
}

int ft_export(t_process *process)
{
	char	**local;
	char	*line;
	int		idx;

	local = process->envs->static_env;
	line = ft_construct(process->tokens, NULL);
	idx = ft_mapitem_index(local, line);
	if (!ft_strchr(line, '='))
	{
		if (idx < 0)
			return (1);
		if (ft_mapitem_index(process->envs->parent_env, local[idx]) < 0)
		{
			if (!ft_mapitem_add(&process->envs->parent_env, local[idx]))
				return (perror("malloc"), exit(EXIT_FAILURE), 0);
		}
		return (free(line), 1);
	}
	update(&process->envs->parent_env, line);
	update(&process->envs->static_env, line);
	if (ft_mapitem_index(process->envs->parent_env, line) < 0 && idx < 0 && \
		!ft_mapitem_add(&process->envs->parent_env, line))
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	transfer(process, line);
	return (free(line), 1);
}

int	ft_env(t_process *process)
{
	char    **ptr;

	if (!process || !*process->envs->parent_env)
		return (0);
	ptr = process->envs->parent_env;
	while (*ptr)
	{
		ft_printf("%s\n", *ptr);
		ptr++;
	}
	return (1);
}

int ft_pwd(t_process *process)
{
	char	*dir_path;
	char	*haystack;
	char	*needle;

	haystack = ft_getcwd();
	needle = process->prompt->shell_name;
	if (needle[0] == '.' && needle[1] == '/')
		needle += 1;
	dir_path = ft_strnstr(haystack, needle, ft_strlen(haystack));
	if (!dir_path)
		return (0);
	ft_printf("%s\n", dir_path);
	free(haystack);
	return (1);
}

static int	remove_var(char ***env, char *var_name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], var_name, len) && (*env)[i][len] == '=')
		{
			if (ft_mapitem_del(env, i))
				return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_process **process)
{
	t_list	*ptr;
	char	*var_name;
	

	if (!process || !(*process)->envs->parent_env)
		return (0);
	ptr = (*process)->tokens->next;
	while (ptr)
	{
		var_name = (char *)ptr->content;
		remove_var(&(*process)->envs->parent_env, var_name);
		ptr = ptr->next;
	}
	return (1);
}

// INPUT PARSE UTILS

static void	assign_value(char **env, char **dest, char *var_name)
{
	char	*value;
	int		idx;
	int		size;
	
	idx = 0;
	while (env && env[idx])
	{
		size = -1;
		if (ft_strchr(env[idx], '='))
			size = ft_strchr(env[idx], '=') - env[idx];
		if (size >= 0 && !ft_strncmp(env[idx], var_name, size) && \
			env[idx][size] == '=')
		{
			value = ft_strdup(ft_strchr(env[idx], '=') + 1);
			*dest = ft_strjoin_free(*dest, value);
			if (!value || !*dest)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			break ;
		}
		idx++;
	}
}

int	already_exists(char **env, char *var_name)
{
	int	idx;
	int size;
	
	idx = 0;

    while (env && env[idx])
	{
        size = -1;
        if (ft_strchr(env[idx], '='))
		    size = ft_strchr(env[idx], '=') - env[idx];
		if (size >= 0 && !ft_strncmp(env[idx], var_name, size))
			return (1);
		idx++;
	}
	return (0);
}

char	*clean_line(char *content, char token)
{
	char    *seq;
	char	*new;
	int     i;

	i = 0;
	new = NULL;
	seq = "`\"\\";
	if (token == 'n')
		seq = " tn`\"'\\*?[]#&;|<>()~";    
	while (content[i] != '\0')
	{
		if (content[i] == '\\' && ft_strchr(seq, content[i + 1]))
		{
			i++;
			new = ft_addchar(new, content[i]);
		}
		else
			new = ft_addchar(new, content[i]);
		i++;
	}
	return (free(content), new);
}

void    scan_char(t_process *process, char *content, char **var_name, int *idx)
{
	char    *stop;

	stop = " \t\n/.,:-+=?!@#^&*()[]{}'\"\\|<>;~";
	if (content[*idx] == '\\' && content[*idx + 1] == '$')
	{
		(*idx)++;
		return ;
	}
	else if (content[*idx] == '$')
	{
		(*idx)++;
		if (special_variable(process, var_name, content[*idx]))
			return ;
		while (content[*idx] && !ft_strchr(stop, content[*idx]))
		{
			*var_name = ft_addchar(*var_name, content[*idx]);
			(*idx)++;
		}
	}
	return ;
}

void	insert_value(t_process *process, char **dest, char *var_name)
{
	char	**process_env;
	char	**static_env;

	process_env = process->envs->parent_env;
	static_env = process->envs->static_env;
	if (already_exists(static_env, var_name))
		assign_value(static_env, dest, var_name);
	else if (already_exists(process_env, var_name))
		assign_value(process_env, dest, var_name);
}

static void	quote_pos_aux(char **str, int *idx, int *slash)
{
	while ((*str)[*idx] == '\\')
	{
		(*slash)++;
		(*idx)++;
	}   
}

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
		quote_pos_aux(&str, &idx, &slash);
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

int quotes_left(char *line_left)
{
	if (!line_left || !*line_left)
		return (0);
	if (ft_strchr(line_left, '\'') || ft_strchr(line_left, '"'))
		return (1);
	return (0);
}

int first_occurrence(t_process *process, char *line, char delim)
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
			return(perror("malloc"), exit(EXIT_FAILURE), 0);
		chunk = ft_parse_token(process, chunk, 'n');
		ft_lstadd_back(&process->tokens, ft_lstnew(chunk));
	}
	return (idx);
}

char	quote_delimiter(char *line)
{
	int	dquote;
	int	squote;

	dquote = quote_pos(line, '"', 1);
	squote = quote_pos(line, '\'', 1);
	if (dquote >= 0 && (squote < 0 || (squote >= 0 && dquote < squote)))
		return ('"');
	else if (squote >= 0)
		return ('\'');	
	return (0);
}

int add_variable(char ***map, char *item)
{
    size_t idx;

    if (!item)
        return (0);
    if (already_exists(*map, item))
    {
        idx = ft_mapitem_index(*map, item);
        if (!ft_mapitem_replace(map, item, idx))
            return (0);
    }
    if (!ft_mapitem_add(map, item))
        return (0);
    return (1);
}

int	contains_variable(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (line[i] == '=')
		return (1);
	return (0);
}

int special_variable(t_process *proc, char **var_name, char ch)

static char	*safe_value(char *line)
{
	char	*value;
	int		idx_line;
	bool	dq;
	bool	sq;
	size_t	len;
	
	idx_line = 0;
	dq = false;
	sq = false;
	while (line[idx_line])
	{
		if (line[idx_line] == ' ' && !dq && !sq)
			break;
		else if (line[idx_line] == '"' && !sq)
			dq = !dq;
		else if (line[idx_line] == '\'' && !dq)
			sq = !sq;
		idx_line++;
	}
	len = idx_line;
	value = ft_substr(line, 0, len);
	if(!value)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return(value);
}

static char	*construct_variable(char *name, char *value)
{
	char	*variable;

	variable = NULL;
	variable = ft_strdup(name);
	if (!variable)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	if (!ft_strchr(value, '='))
		variable = ft_addchar(variable, '=');
	if (!variable)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	variable = ft_strjoin_free(variable, value);
	if (!variable)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (variable);
}

static void	trimmer(char **line, char *delim)
{
	char	*res;
	char	*line_from_delim;
	int		line_len;
	int		from_idx;

	res = NULL;
	line_len = ft_strlen(*line);
	line_from_delim = ft_strnstr(*line, delim, line_len);
	from_idx = line_len - ft_strlen(line_from_delim);
	from_idx += ft_strlen(delim);
	if ((*line)[from_idx])
	{
		res = ft_strdup(*line + from_idx);
		if (!res)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	free(*line);
	*line = res;	
}

static int	add_to_process_env(t_process *process, char *name, char *value)
{
	char	*var;
	int		idx;

	var = construct_variable(name, value);
	idx = ft_mapitem_index(*&process->envs->static_env, var);
	if (idx >= 0 && !ft_mapitem_replace(&process->envs->static_env, var, idx))
		return (0);
	else if (!ft_mapitem_add(&process->envs->static_env, var))
		return (0);
	return (free(var), free(name), 1);
}

int	ft_inputvar(t_process *process, char **line)
{
	char	*name;
	char	*value;

	name = ft_strtok(*line, "=");
	value = safe_value(ft_strchr(*line, '='));
	process->is_variable = true;
	if (!ft_std(process, value) && !ft_quote(process, value))
		return (0);
	trimmer(line, value);
	value = ft_construct(process->tokens, value);
	if (!add_to_process_env(process, name, value))
		return (0);
	ft_lstclear(&process->tokens, free);
	process->tokens = NULL;
	process->is_variable = false;
	ft_clear_strtok();
	return (1);
}

int	ft_parse_line(t_process *process)
{
	char	*cmd;
	char    *ptr_line;

	if (contains_variable(process->line))
	{
        ft_putstr_fd("here in parse line1\n", 1);
		if (!ft_inputvar(process, &process->line))
			return (0);
        ft_putstr_fd("here in parse line2\n", 1);
	}
	ptr_line = process->line;
	cmd = ft_strtok(ptr_line, " ");
	ft_lstadd_back(&process->tokens, ft_lstnew(cmd));
	if (!ft_strchr(ptr_line, ' '))
		return (1);
	if (!ft_std(process, ptr_line) && !ft_quote(process, ptr_line))
		return (0);
	return (1);
}

static int	parse_aux(t_process *process, char **res, char **var_name)
{
	if (process->is_special == false)
	{
		insert_value(process, res, *var_name);
		free(*var_name);
		*var_name = NULL;
	}
	else
	{
		*res = ft_strjoin_free(*res, *var_name);
		*var_name = NULL;
	}
	if (!*res)
		return (0);
	return (1);
}

char	*ft_parse_token(t_process *process, char *content, char token)
{
	char	*res;
	char	*var_name;
	int		i;

	if (!content || !*content)
		return (NULL);
	content = clean_line(content, token);
	res = NULL;
	i = 0;
	while (content[i] != '\0')
	{
		var_name = NULL;
		scan_char(process, content, &var_name, &i);
		if (var_name == NULL)
		{
			res = ft_addchar(res, content[i]);
			i++;
		}
		else if (!parse_aux(process, &res, &var_name))
            return (perror("malloc"), exit(EXIT_FAILURE), NULL);
			
	}
	return (free(content), res);	
}

static int reconstruct_token(t_process *process, char *line, char delim)
{
	char	*res;
	int		start_idx;
	int		end_idx;

	start_idx = first_occurrence(process, line, delim);
	if (start_idx < 0)
		return (-1);
	start_idx += 1;
	end_idx = quote_pos(line, delim, 2) - start_idx;
	res = ft_substr(line, start_idx, end_idx);
	if (!res)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	if (delim == '"')
		res = ft_parse_token(process, res, 'd');
	ft_lstadd_back(&process->tokens, ft_lstnew(res));
	return (1);
}

static char	*standard_token(t_process *process, char *line)
{
	char    *added;
	char    *line_left;
	size_t	next;
	
	added = ft_strtok(line, " ");
	if (!added)
		return (NULL);
	next = ft_strlen(added) + 1;
	added = ft_parse_token(process, added, 'n');
	if (!added)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	ft_lstadd_back(&process->tokens, ft_lstnew(added));
	if (ft_strchr(line, ' '))
	{
			line_left = ft_strdup(line + next);
			if (!line_left)
				return (perror("malloc"), exit(EXIT_FAILURE), NULL);
			ft_addspace(&process->tokens);
			return (free(line), line_left);
	}
	else
		free(line);
	return (line = NULL, NULL);
}

static char	*quotes_token(t_process *process, char *line, char delim)
{
	char	*line_left;
	int		indexes_left;
	int		last_index;
	int		paired_delim;
	
	line_left = NULL;
	if (reconstruct_token(process, line, delim) < 0)
		return (NULL);
	indexes_left = 0;
	last_index = ft_strlen(line) - 1;
	paired_delim = quote_pos(line, delim, 2);
	if (paired_delim < last_index)
		indexes_left = last_index - paired_delim;
	if (indexes_left > 0)
	{
		line_left = ft_substr(line, paired_delim + 1, indexes_left);
		if (!line_left)
			return (perror("malloc"), exit(EXIT_FAILURE), NULL);
		if (line_left[0] == ' ')
			ft_addspace(&process->tokens);
	}
	return (free(line), line_left);
}

int	ft_quote(t_process *process, char *line)
{
	char	*line_args;
    char    delimiter;

    if (ft_strchr(line, ' ') && process->is_variable == false)
		line_args = ft_strdup(ft_strchr(line, ' ') + 1);
	else
		line_args = ft_strdup(line);
	if (!line_args)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
    ft_clear_strtok();
    while (line_args && *line_args)
	{
		delimiter = quote_delimiter(line_args);
        if (delimiter == 0)
            line_args = standard_token(process, line_args);
        else
            line_args = quotes_token(process, line_args, delimiter);
	}		
	return (1);
}

static char	*get_content(t_process *process, char *line)
{
	char	*content;

	content = NULL;
	if (process->is_variable)
	{
		ft_clear_strtok();
		content = ft_strtok(line, "=");
	}
	else
		content = ft_strtok(NULL, " ");
	if (!content)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (content);
}

int		ft_std(t_process *process, char *line)
{
	char    *token;
	char	*node;

	if (ft_strchr(line, '"') || ft_strchr(line, '\''))
		return (0);
	token = get_content(process, line);
	while (token)
	{
		node = ft_parse_token(process, token, 'n');
		if (!node)
			return (perror("malloc"), exit(EXIT_FAILURE), 0);
        ft_lstadd_back(&process->tokens, ft_lstnew(node));
		token = ft_strtok(NULL, " ");
		if (token)
			ft_addspace(&process->tokens);
	}
	return (1);
}

char	*ft_prompt(t_process *process)
{
	char	*current_path;
	char	*home_path;
	char	*buffer;
	char	*prompt;
	size_t	size_current;
	size_t  size_home;
	
	current_path = process->prompt->current_wd;
	home_path = process->prompt->home_path;
	size_current = ft_strlen(current_path);
	size_home = ft_strlen(home_path);
	if (!ft_strncmp(current_path, home_path, size_current))
	{
		prompt = ft_strjoin(">/~", PROMPT_ARROW);
		if (!prompt)
			return (perror("malloc"), exit(EXIT_FAILURE), NULL);
		return (prompt); 
	}
	buffer = ft_strnstr(current_path, home_path, size_current) + size_home;
	prompt = ft_strjoin(">/~", buffer);
	buffer = ft_strjoin(prompt, PROMPT_ARROW);
	if (!prompt || !buffer)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (free(prompt), buffer);
}

void	ft_readinput(t_process *process)
{
	process->prompt->display = ft_prompt(process);
	if (process->prompt->display == NULL)
	{
        perror("malloc");
        return ;
    }
    ft_putstr_fd("here in readinput\n", 1);
	process->line = readline(process->prompt->display);
	if (process->line == NULL || *(process->line) == '\0')
		return ;
	add_history(process->line);
	ft_parse_line(process);
}

// MAIN FUNCTIONS

static void	add_last_arg(t_process *process)
{
	t_list	*last_node;
	
	last_node = NULL;
	if (process->tokens)
		last_node = ft_lstlast(process->tokens);
	if (process->last_arg && *(process->last_arg))
		free(process->last_arg);
	if (last_node)
	{
		process->last_arg = ft_strdup((char *)last_node->content);
		if (!process->last_arg)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
		
}

void	reset_utils(t_process **process)
{
	if ((*process)->line)
		free((*process)->line);
	add_last_arg(*process);
	ft_clear_strtok();
	if ((*process)->tokens)
		ft_lstclear(&(*process)->tokens, free);
	(*process)->tokens = NULL;
	if ((*process)->prompt->display)
		free((*process)->prompt->display);
	(*process)->prompt->display = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_process  	*process;

	if (argc > 2)
		return (0);
	process = NULL;
	if (!init_parent(&process, argv[0], envp))
		return (0);
	while (1)
	{
		signal(SIGINT, ft_sigint);
		ft_readinput(process);
		if (process->tokens && !ft_builtins(process))
			ft_printf("%s: command not found\n", (char *)process->tokens->content);
		reset_utils(&process);
	}
	return (0);
}


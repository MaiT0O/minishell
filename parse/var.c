/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:06:45 by ebansse           #+#    #+#             */
/*   Updated: 2025/06/23 15:06:46 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_braces(char *line, int *i, int *has_braces)
{
	*has_braces = 0;
	if (line[++(*i)] == '{')
	{
		*has_braces = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

static char	*get_env_key(char *line, int *i, int has_braces)
{
	int		start_env;
	size_t	env_len;

	start_env = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_')
		&& (!has_braces || line[*i] != '}'))
		(*i)++;
	env_len = *i - start_env;
	if (env_len == 0)
	{
		(*i)--;
		return (NULL);
	}
	return (substrdup(line, start_env, env_len));
}

static int	substitute_env_value(t_env *env, char *key, char **result)
{
	char	*val;
	char	*tmp;

	if (!key)
	{
		*result = str_append_char(*result, '$');
		return (0);
	}
	val = get_env_value(env, key);
	if (val)
	{
		tmp = *result;
		*result = ft_strjoin(*result, val);
		if (tmp)
			free(tmp);
	}
	return (1);
}

int	handle_env_var(t_env *env, char *line, int *i, char **result)
{
	char	*key;
	int		has_braces;

	check_braces(line, i, &has_braces);
	key = get_env_key(line, i, has_braces);
	if (!substitute_env_value(env, key, result))
		return (0);
	free(key);
	if (has_braces)
	{
		if (line[*i] != '}')
		{
			ft_putstr_fd("minishell: syntax error: missing closing brace\n", 2);
			return (0);
		}
	}
	else
		(*i)--;
	return (1);
}

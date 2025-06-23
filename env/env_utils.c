/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cesar.guinot66@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:40:39 by cguinot           #+#    #+#             */
/*   Updated: 2025/06/04 20:03:28 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_env));
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->next = *env;
	*env = tmp;
}

static char	**fill_env_array(t_env *env, char **env_array, int count)
{
	int		i;
	char	*temp;
	t_env	*current;

	i = 0;
	current = env;
	while (current && i < count)
	{
		if (current->value)
		{
			temp = ft_strjoin(current->key, "=");
			env_array[i] = ft_strjoin(temp, current->value);
			free(temp);
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	**env_list_to_array(t_env *env)
{
	char	**env_array;
	int		count;
	t_env	*current;

	if (!env)
		return (NULL);
	count = 0;
	current = env;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	return (fill_env_array(env, env_array, count));
}

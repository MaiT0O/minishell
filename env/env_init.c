/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cesar.guinot66@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:37:27 by cguinot           #+#    #+#             */
/*   Updated: 2025/05/26 17:02:33 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*ft_copy_envp_to_list(char **envp, int i)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*sep;
	char	*key;
	char	*value;

	env_list = NULL;
	while (envp[i])
	{
		sep = ft_strchr(envp[i], '=');
		if (sep)
		{
			key = ft_substr(envp[i], 0, sep - envp[i]);
			value = ft_strdup(sep + 1);
			new_node = ft_env_new(key, value);
			free(key);
			free(value);
			ft_env_add_back(&env_list, new_node);
		}
		i++;
	}
	return (env_list);
}

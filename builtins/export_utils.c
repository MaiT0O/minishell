/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:05:53 by ebansse           #+#    #+#             */
/*   Updated: 2025/06/23 15:06:01 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_next_sorted(t_env *env, char *last)
{
	t_env	*min;

	min = NULL;
	while (env)
	{
		if ((!last || ft_strcmp(env->key, last) > 0)
			&& (!min || ft_strcmp(env->key, min->key) < 0))
			min = env;
		env = env->next;
	}
	return (min);
}

int	ft_export_display(t_env *env)
{
	char	*last;
	t_env	*next;

	last = NULL;
	while (1)
	{
		next = find_next_sorted(env, last);
		if (!next)
			break ;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(next->key, 1);
		if (next->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(next->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		free(last);
		last = ft_strdup(next->key);
	}
	free(last);
	return (0);
}

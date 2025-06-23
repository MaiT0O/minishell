/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cesar.guinot66@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:18:12 by cguinot           #+#    #+#             */
/*   Updated: 2025/06/05 16:16:12 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_get_path(char **args, t_env *env)
{
	char	*home;

	if (!args[1])
	{
		home = get_env_value(env, "HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
		return (ft_strdup(home));
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	return (ft_strdup(args[1]));
}

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	path = cd_get_path(args, *env);
	if (!path)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		free(path);
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (oldpwd)
		set_env_value(env, "OLDPWD", oldpwd);
	if (newpwd)
		set_env_value(env, "PWD", newpwd);
	free(path);
	free(oldpwd);
	free(newpwd);
	return (0);
}

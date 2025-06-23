/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cesar.guinot66@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:43:55 by cguinot           #+#    #+#             */
/*   Updated: 2025/06/05 17:58:57 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	else
	{
		path_env = get_env_value(env, "PATH");
		if (!path_env)
			return (NULL);
		paths = ft_split(path_env, ':');
		if (!paths)
			return (NULL);
		return (search_in_paths(cmd, paths));
	}
}

char	*search_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

int	pid_cas(t_cmd *cmd, char **env_array, char *command_path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		apply_file_redirections(cmd->redir);
		execve(command_path, cmd->argv, env_array);
		perror("minishell");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(command_path);
		ft_free_array(env_array);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	else
		return (free(command_path), ft_free_array(env_array), 1);
}

int	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	*command_path;
	char	**env_array;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	command_path = find_command_path(cmd->argv[0], shell->env);
	if (!command_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	env_array = env_list_to_array(shell->env);
	if (!env_array)
	{
		free(command_path);
		return (1);
	}
	return (pid_cas(cmd, env_array, command_path));
}

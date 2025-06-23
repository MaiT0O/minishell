/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cesar.guinot66@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:30:50 by cguinot           #+#    #+#             */
/*   Updated: 2025/06/05 18:00:16 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_quit(int exit_code)
{
	exit(exit_code);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	save_in;
	int	save_out;
	int	result;

	if (apply_redirections_builtin(cmd->redir, &save_in, &save_out) != 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		result = ft_echo(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		result = ft_cd(cmd->argv, &shell->env);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		result = ft_pwd();
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		result = ft_export(cmd->argv, &shell->env);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		result = ft_unset(cmd->argv, &shell->env);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		result = ft_env(shell->env);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd->argv, shell->last_status);
	else
		result = 0;
	return (dup2(save_in, STDIN_FILENO), dup2(save_out, STDOUT_FILENO),
		close(save_in), close(save_out), result);
}

void	execute_commands(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (cmd->next)
	{
		exit_status = execute_pipeline(cmd, shell);
	}
	else
	{
		if (is_builtin(cmd->argv[0]))
			exit_status = execute_builtin(cmd, shell);
		else
			exit_status = execute_external(cmd, shell);
	}
	shell->last_status = exit_status;
}

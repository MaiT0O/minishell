/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cesar.guinot66@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:36:31 by cguinot           #+#    #+#             */
/*   Updated: 2025/06/05 17:10:53 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_commands_in_list(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	create_all_pipes(t_pipe_data *data)
{
	int	i;

	data->nb_pipes = data->nb_commands - 1;
	if (data->nb_pipes <= 0)
		return (0);
	i = 0;
	while (i < data->nb_pipes)
	{
		if (pipe(data->pipes[i]) == -1)
		{
			perror("minishell: pipe");
			return (-1);
		}
		i++;
	}
	return (data->nb_pipes);
}

void	close_all_pipes(t_pipe_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipes)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

void	setup_redirections(t_pipe_data *data, int cmd_index)
{
	if (cmd_index > 0)
		dup2(data->pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < data->nb_commands - 1)
		dup2(data->pipes[cmd_index][1], STDOUT_FILENO);
}

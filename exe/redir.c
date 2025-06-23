/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cesar.guinot66@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:28:32 by cguinot           #+#    #+#             */
/*   Updated: 2025/06/05 17:41:47 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = readline("");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	return (fd);
}

static int	open_redir_file(t_redir *redir)
{
	if (redir->type == T_REDIR_IN)
		return (open(redir->filename, O_RDONLY));
	else if (redir->type == T_REDIR_OUT)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == T_REDIR_APPEND)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (redir->type == T_HEREDOC)
		return (open_heredoc(redir->filename));
	return (-1);
}

void	apply_file_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		fd = open_redir_file(redir);
		if (fd >= 0)
		{
			if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}

int	apply_redirections_builtin(t_redir *redir_list, int *save_in, int *save_out)
{
	int	fd;

	*save_in = dup(STDIN_FILENO);
	*save_out = dup(STDOUT_FILENO);
	while (redir_list)
	{
		fd = open_redir_file(redir_list);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(redir_list->filename);
			return (1);
		}
		if (redir_list->type == T_REDIR_IN || redir_list->type == T_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir_list = redir_list->next;
	}
	return (0);
}

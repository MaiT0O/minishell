/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:15:41 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/22 16:51:30 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_status_to_result(char **result, int last_status, int *i)
{
	char	*status_str;
	char	*new_result;

	status_str = ft_itoa(last_status);
	if (!status_str)
		return ;
	new_result = ft_strjoin(*result, status_str);
	free(*result);
	free(status_str);
	*result = new_result;
	(*i)++;
}

char	*expand_variables(t_env *env, char *line, t_shell *shell)
{
	char	*result;
	int		i;

	result = NULL;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 39)
		{
			if (!handle_single_quote(line, &i, &result))
				return (NULL);
		}
		else if (line[i] == '$' && line[i + 1] == '?' )
			append_status_to_result(&result, shell->last_status, &i);
		else if (line[i] == '$' && line[i + 1] && (ft_isalpha(line[i + 1])
				|| line[i + 1] == '_' || line[i + 1] == '{'))
		{
			if (!handle_env_var(env, line, &i, &result))
				return (free(line), NULL);
		}
		else
			result = str_append_char(result, line[i]);
	}
	free (line);
	return (result);
}

int	process_line(char *line, t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*lst;
	char	*expand;

	expand = expand_variables(shell->env, line, shell);
	if (!expand)
		return (0);
	lst = lexer(expand);
	cmd = parse_tokens(lst);
	if (cmd)
	{
		setup_signals(1);
		execute_commands(cmd, shell);
	}
	free_tokens(lst);
	free_cmd(cmd);
	return (1);
}

void	prompt_loop(t_shell *shell)
{
	char	*line;

	message();
	while (1)
	{
		setup_signals(0);
		if (!isatty(STDIN_FILENO))
			dup2(open("/dev/tty", O_RDONLY), STDIN_FILENO);
		line = readline(PROMPT_PRINT);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		check_and_handle_signals(shell);
		if (line && *line && ft_strlen(line) > 0)
		{
			add_history(line);
			process_line(ft_strdup(line), shell);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_env	*env;

	(void)argc;
	(void)argv;
	shell.last_status = 0;
	shell.running = 1;
	env = ft_copy_envp_to_list(envp, 0);
	shell.env = env;
	if (!env)
	{
		ft_putendl_fd("env copy failed", 2);
		return (1);
	}
	setup_signals(0);
	prompt_loop(&shell);
	free_env(env);
	rl_clear_history();
	return (0);
}

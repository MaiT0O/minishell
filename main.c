/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:15:41 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/26 17:26:17 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_loop(t_shell *shell)
{
	char	*line;
	t_cmd	*cmd;
	t_token	*lst;

	cmd = NULL;
	message();
	while (1)
	{
		line = readline(PROMPT_PRINT);
		if (!line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*line)
			add_history(line);

		/*// (Étape future) analyse syntaxique
		cmd = parse_input(line);
		if (cmd)
			execute_commands(cmd, shell); // exécute la/les commande(s)

		free_cmds(cmd);*/
		lst = lexer(line, shell->env);
		if (!lst)
			continue ;
		print_token(lst);
		/*cmd = parse_input(lst);*/
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_env	*envi;

	(void)argc;
	(void)argv;

	shell.last_status = 0;
	shell.running = 1;
	envi = ft_copy_envp_to_list(envp, 0);
	if (!envi)
	{
		ft_putendl_fd(*envp, 0);
		return (1);
	}
	shell.env = envi;
	ft_env(envi);
	prompt_loop(&shell);

	/*free_env(shell.env);*/
	return (0);
}

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

void	prompt_loop(t_shell *shell)
{
	char	*line;
	t_cmd	*cmd;

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

		// (Étape future) expansion des variables d'environnement
		/*line = expand_variables(line, shell->env);

		// (Étape future) analyse syntaxique
		cmd = parse_input(line);
		if (cmd)
			execute_commands(cmd, shell); // exécute la/les commande(s)

		free_cmds(cmd);*/
		free(line);
	}
}

int	main(int argc, char **argv)
{
	t_shell	shell;

	(void)argc;
	(void)argv;

	/*shell.env = init_env(envp);*/ // à écrire : copie de envp dans t_env*
	shell.last_status = 0;
	shell.running = 1;

	prompt_loop(&shell);

	/*free_env(shell.env);*/
	return (0);
}

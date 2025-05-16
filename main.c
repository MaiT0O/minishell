#include "minishell.h"

void	prompt_loop(t_shell *shell)
{
	char	*line;
	t_cmd	*cmd;

	while (1)
	{
		// Affiche le prompt et lit l'entrée utilisateur
		line = readline("minishell$ ");
		if (!line) // Ctrl+D (EOF)
		{
			write(1, "exit\n", 5);
			break;
		}

		if (*line)
			add_history(line); // Historique (si readline est autorisé)

		// (Étape future) expansion des variables d'environnement
		/*line = expand_variables(line, shell->env);

		// (Étape future) analyse syntaxique
		cmd = parse_input(line);
		if (cmd)
			execute_commands(cmd, shell); // exécute la/les commande(s)

		free_cmds(cmd);
		free(line);*/
	}
}

int	main(int argc, char **argv, char **envp)
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

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

// Fichier : token.h ou minishell.h

typedef enum e_token_type
{
	T_WORD,         // Mot générique : "ls", "hello", "file.txt"
	T_PIPE,         // |
	T_REDIR_IN,     // <
	T_REDIR_OUT,    // >
	T_REDIR_APPEND, // >>
	T_HEREDOC       // <<
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

//🧠 Structure représentant une variable d'environnement
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//🔧 Structure de redirection (>, >>, <)
typedef struct s_redir
{
	int				type;		// 0: < | 1: > | 2: >>
	char			*filename;
	struct s_redir	*next;
}	t_redir;

//📦 Structure d'une commande unique
typedef struct s_cmd
{
	char			**argv;		 // arguments (argv[0] = commande)
	t_redir			*redir;		 // liste des redirections
	struct s_cmd	*next;		 // prochaine commande (pipe)
}	t_cmd;

//🌍 Structure de contexte global du shell
typedef struct s_shell
{
	t_env	*env;		 // liste chaînée de l'environnement
	int		last_status; // $? dernière valeur de retour
	int		running;	 // état du shell (utile pour signaux)
}	t_shell;

/*lexer.c*/
t_token	*lexer(char *line, t_env *env);
int	count_word_tokens(t_token *head);

/*utils.c*/
bool	ft_isspace(char c);
char	*substrdup(const char *src, int start, int len);
void	message(void);

/*parser.c*/
void	print_token(t_token *lst);
t_cmd	*parse_tokens(t_token *tokens);
t_token *test_lexer(char *line);

/*env*/
t_env	*ft_copy_envp_to_list(char **envp, int i);
void	set_env_value(t_env **env, const char *key, const char *value);
char	*get_env_value(t_env *env, const char *key);
void	ft_env(t_env *env);

/*free.c*/
void	free_tokens(t_token *head);
void	free_env(t_env *env);

# define PROMPT_PRINT "\033[1;35mminishell $ \033[0m"
# define MEMORY_ERROR "Memory allocation error"
# define COMMAND_NOT_FOUND "Command not found"
# define PERMISSION_DENIED "Permission denied"
# define FILE_NOT_FOUND "No such file or directory"
# define INVALID_REDIR "Invalid redirection syntax"
# define HEREDOC_EOF "heredoc EOF reached"
# define HEREDOC_ERROR "Heredoc error"

#endif
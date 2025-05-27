/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:29:35 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/26 17:30:08 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_cmd *cmd, int type, char *filename)
{
	t_redir *tmp;
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = type;
	redir->filename = ft_strdup(filename);
	redir->next = NULL;

	// Ajout à la fin de la liste
	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

char	**extract_word_tokens(t_token *tokens)
{
    int		nb;
    int		i;
    char	**argv_parts;

    nb = count_word_tokens(tokens);
    argv_parts = malloc(sizeof(char *) * (nb + 1));
    if (!argv_parts)
        return (NULL);
    i = 0;
    while (tokens)
    {
        if (tokens->type == T_WORD)
            argv_parts[i++] = ft_strdup(tokens->value);
        tokens = tokens->next;
    }
    argv_parts[i] = NULL;
    return (argv_parts);
}

bool	extract_redir_token(t_token *tokens, t_cmd *curr_cmd)
{
	while (tokens)
	{
		if (tokens->type >= T_REDIR_IN && tokens->type <= T_HEREDOC)
		{
			if (!tokens->next || tokens->next->type != T_WORD)
				return (printf(INVALID_REDIR), false);
			add_redirection(curr_cmd, tokens->type, tokens->next->value);
		}
		tokens = tokens->next;
	}
	return (true);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;
	char	**argv_parts;
	int		i;

	cmd_list = NULL;
	curr_cmd = malloc(sizeof(t_cmd));
	i = 0;
	if (!tokens)
		return (printf("tokens is NULL\n"), NULL);
	argv_parts = extract_word_tokens(tokens);
	if (argv_parts == NULL)
		return (NULL);
	if (extract_redir_token(tokens, curr_cmd) == false)
		return (NULL);
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:47:47 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/16 17:34:34 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	if (!*head)
		*head = new;
	else
	{
		t_token *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	tokenisation(t_token *head, char *line, int i)
{
	int	start;

	start = 0;
	if (line[i] == '>' && line[i + 1] == '>')
		return (add_token(&head, new_token(ft_strdup(">>"), T_REDIR_APPEND))
			, i += 2);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (add_token(&head, new_token(ft_strdup("<<"), T_HEREDOC))
			, i += 2);
	else if (line[i] == '|')
		return (add_token(&head, new_token(ft_strdup("|"), T_PIPE)), i++);
	else if (line[i] == '<')
		return (add_token(&head, new_token(ft_strdup("<"), T_REDIR_IN)), i++);
	else if (line[i] == '>')
		return (add_token(&head, new_token(ft_strdup(">"), T_REDIR_OUT)), i++);
	else
	{
		start = i;
		while (line[i] && !ft_isspace(line[i]) && line[i] != '|'
			&& line[i] != '<' && line[i] != '>')
			i++;
		return (add_token(&head, new_token(substrdup(line, start, i - start)
			, T_WORD)), i);
	}
	return (i);
}

t_token	*lexer(char *line)
{
	int i;
	int res;
    int start;
    t_token	*head;

	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue;
		}
		i = tokenisation(head, line, i);
	}
    
}

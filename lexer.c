/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:47:47 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/26 17:44:09 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word_tokens(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == T_WORD)
			count++;
		head = head->next;
	}
	return (count);
}

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
	t_token	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	tokenisation(t_token **head, char *line, int i)
{
	int	start;

	start = 0;
	if (line[i] == '>' && line[i + 1] == '>')
		return (add_token(head, new_token(ft_strdup(">>"), T_REDIR_APPEND))
			, i += 2);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (add_token(head, new_token(ft_strdup("<<"), T_HEREDOC))
			, i += 2);
	else if (line[i] == '|')
		return (add_token(head, new_token(ft_strdup("|"), T_PIPE)), ++i);
	else if (line[i] == '<')
		return (add_token(head, new_token(ft_strdup("<"), T_REDIR_IN)), ++i);
	else if (line[i] == '>')
		return (add_token(head, new_token(ft_strdup(">"), T_REDIR_OUT)), ++i);
	else
	{
		start = i;
		while (line[i] && !ft_isspace(line[i]) && line[i] != '|'
			&& line[i] != '<' && line[i] != '>')
			i++;
		return (add_token(head, new_token(substrdup(line, start, i - start)
					, T_WORD)), i);
	}
	return (i);
}

bool	lex_double_quote(t_token *head, t_env *env, char *line, int i)
{
	int		start_quote;
	int		start_env;
	size_t	env_len;

	start_quote = i + 1;
	while (line[++i] && line[i] != 34)
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			i++;
			start_env = i;
			while (ft_isalnum(line[i]) || line[i] == '_')
				i++;
			env_len = i - start_env;
			

		}
	}
	if (line[i] == '\0')
		return (printf("Unclosed double quote\n"), false);
}
t_token	*lexer(char *line, t_env *env)
{
	int			i;
	int			start_quote;
	int			start_env;
	int			end_env;
	t_token		*head;

	head = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			start_quote = i+1;
			while (line[++i] && line[i] != 39);
			if (line[i] == '\0')
				return (printf("Unclosed single quote\n"), NULL);
			add_token(head, new_token(substrdup(line, start_quote, i - start_quote)
				, T_WORD));
		}
		if (line[i] == 34)
		{
			
		}
		if (ft_isspace(line[i]))
		{
			i++;
			continue ;
		}
		i = tokenisation(&head, line, i);
	}
	return (head);
}

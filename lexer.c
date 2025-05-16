/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:47:47 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/16 17:00:41 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substrdup(const char *src, int start, int len)
{
	char	*str;
	int		i;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && src[start + i])
	{
		str[i] = src[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

bool	add_token(t_token **head, t_token *new)
{
	if (!*head)
	{
		*head = new;
		return (true);
	}
	else
	{
		t_token *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (true);
}

bool	tokenisation(t_token *head, char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
		add_token(&head, new_token(ft_strdup(">>"), T_REDIR_APPEND));
	else if (line[i] == '<' && line[i + 1] == '<')
		add_token(&head, new_token(ft_strdup("<<"), T_HEREDOC));
	else if (line[i] == '|')
		add_token(&head, new_token(ft_strdup("|"), T_PIPE));
	else if (line[i] == '<')
		add_token(&head, new_token(ft_strdup("<"), T_REDIR_IN));
	else if (line[i] == '>')
	{
		add_token(&head, new_token(ft_strdup(">"), T_REDIR_OUT));
		return (i++);
	}
}

t_token	*lexer(char *line)
{
	int i;
	int res;
    int start;
    t_token	*head;

	while (line[i])
	{
		if (line[i] == 32 || (line[i] >= 7 && line[i] <= 13))
		{
			i++;
			continue;
		}
		res = i;
		i = tokenisation(head, line, i);
		if (res == i)
		{
			start = i;
			while (line[i] && !isspace(line[i]) && line[i] != '|' &&
					line[i] != '<' && line[i] != '>') {
				i++;
			}
			add_token(&head, new_token(substrdup(line, start, i - start), T_WORD));
		}
	}
    
}

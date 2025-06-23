/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:47:47 by ebansse           #+#    #+#             */
/*   Updated: 2025/06/04 16:52:16 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		while (line[i] && !ft_isspace(line[i]) && line[i] != '|' && line[i]
			!= '<' && line[i] != '>' && line[i] != 34 && line[i] != 39)
			i++;
		return (add_token(head, new_token(substrdup(line, start, i - start)
					, T_WORD)), i);
	}
	return (i);
}

int	handle_single_quote(char *line, int *i, char **result)
{
	int		start;
	char	*content;
	char	*tmp;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != 39)
		(*i)++;
	if (line[*i] != 39)
	{
		printf("Error: unclosed single quote\n");
		free(*result);
		free(line);
		return (0);
	}
	content = substrdup(line, start, *i - start);
	tmp = *result;
	*result = ft_strjoin(*result, content);
	if (tmp)
		free(tmp);
	free(content);
	return (1);
}

int	handle_quotes(char *line, int *i, t_token **head)
{
	int		start_quote;
	int		quote;

	start_quote = ++(*i);
	quote = line[*i - 1];
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == '\0')
	{
		if (quote == 39)
			return (printf("Unclosed single quote\n"), 0);
		else if (quote == 34)
			return (printf("Unclosed double quote\n"), 0);
	}
	if (line[*i] == quote)
		add_token(head, new_token(substrdup(line, start_quote,
					*i - start_quote), T_WORD));
	(*i)++;
	return (1);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
		{
			if (!handle_quotes(line, &i, &head))
				return (NULL);
		}
		else if (ft_isspace(line[i]))
			i++;
		else
			i = tokenisation(&head, line, i);
	}
	free(line);
	return (head);
}

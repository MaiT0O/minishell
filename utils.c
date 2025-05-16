/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:13:35 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/16 17:27:58 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(char c)
{
	if (c == 32 || (c >= 7 && c <= 13))
		return (true);
	return (false);
}

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

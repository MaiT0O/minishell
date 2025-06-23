/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:11:05 by ebansse           #+#    #+#             */
/*   Updated: 2024/11/08 17:18:20 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const	*s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new;

	i = -1;
	new = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!new)
		return (NULL);
	while (s[++i])
		new[i] = (*f)(i, s[i]);
	new[i] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:40:18 by ebansse           #+#    #+#             */
/*   Updated: 2024/11/08 14:46:47 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	int				j;
	unsigned int	start;
	int				end;
	size_t			len;

	i = 0;
	j = ft_strlen((char *)s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	while (s1[j] && ft_strchr(set, s1[j]))
		j--;
	end = j;
	len = end - start + 1;
	return (ft_substr(s1, start, len));
}

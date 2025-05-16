/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:11:43 by ebansse           #+#    #+#             */
/*   Updated: 2024/11/07 11:11:43 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;
	char	*hay;

	i = -1;
	hay = (char *)haystack;
	needle_len = ft_strlen((char *)needle);
	if (needle_len == 0 || haystack == needle)
		return (hay);
	while (hay[++i] && i < n)
	{
		j = 0;
		while (hay[i + j] == needle[j] && needle[j] && hay[i + j]
			&& i + j < n)
			j++;
		if (j == needle_len)
			return (hay + i);
	}
	return (0);
}

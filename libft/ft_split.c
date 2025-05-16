/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:26:54 by ebansse           #+#    #+#             */
/*   Updated: 2024/11/17 18:22:18 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static void	ft_process(char const *s, char c, int *j, int *k)
{
	while (s[*j] == c && s[*j])
		(*j)++;
	*k = *j;
	while (s[*j] != c && s[*j])
		(*j)++;
}

char	**ft_split(char const *s, char c)
{
	int		nbr;
	char	**dest;
	int		i;
	int		k;
	int		j;

	nbr = ft_countword(s, c);
	dest = (char **)malloc((nbr + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	k = 0;
	j = 0;
	while (s[j])
	{
		ft_process(s, c, &j, &k);
		if (k < j)
		{
			dest[i++] = ft_substr(s, (size_t)k, (size_t)(j - k));
			if (!dest[i - 1])
				return (ft_free_split(dest));
		}
	}
	dest[i] = 0;
	return (dest);
}

/*int	main()
{
	char	**c;
	c = ft_split("salut, tout, le, monde", ',');
	printf("%s\n", c[0]);
	printf("%s\n", ft_strjoin("Bonjour", " les amis"));
	printf("%s\n", ft_strtrim("123Hello World123", "123"));
	return (0);
}*/
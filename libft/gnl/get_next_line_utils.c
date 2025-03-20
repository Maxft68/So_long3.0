/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:46:27 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/19 15:23:06 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s1s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	s1s2 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s1s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s1s2[i] = s1[i];
		i++;
	}
	while (s2[j])
		s1s2[i++] = s2[j++];
	s1s2[i] = '\0';
	return (s1s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*alloc;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup_gnl(""));
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	alloc = malloc((len + 1) * sizeof(char));
	if (!alloc)
		return (NULL);
	ft_strlcpy_gnl(alloc, &s[start], len + 1);
	return (alloc);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*alloc;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	alloc = malloc((l + 1) * sizeof(char));
	if (!alloc)
		return (NULL);
	ft_strlcpy_gnl(alloc, s, l + 1);
	return (alloc);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0 || !dst)
		return (ft_strlen(src));
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:34 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/19 15:23:24 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_all(char **s, char **s1)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
}

int	ft_strchr_int(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != (char)c)
			i++;
		else
			return (i);
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*to_save = NULL;
	t_variable	v;

	v.new_to_save = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_all(&to_save, NULL), NULL);
	v.temp_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!v.temp_read)
		return (free_all(&to_save, NULL), NULL);
	if (to_save && ft_strchr_int(to_save, '\n') != -1)
		return (free_all(&v.temp_read, NULL), ft_separator(&v, &to_save));
	while (1)
	{
		v.bytes_read = read(fd, v.temp_read, BUFFER_SIZE);
		if (v.bytes_read < 0)
			return (free_all(&to_save, &v.temp_read), NULL);
		if (v.bytes_read == 0)
			return (free_all(&v.temp_read, NULL), ft_separator(&v, &to_save));
		v.temp_read[v.bytes_read] = '\0';
		v.temp_save = ft_strjoin_gnl(to_save, v.temp_read);
		free_all(&to_save, NULL);
		to_save = v.temp_save;
		if (ft_strchr_int(v.temp_read, '\n') != -1)
			return (free_all(&v.temp_read, NULL), ft_separator(&v, &to_save));
	}
}

char	*ft_separator(t_variable *v, char **to_save)
{
	if (!to_save || !*to_save)
		return (NULL);
	v->newline_index = ft_strchr_int(*to_save, '\n');
	if (v->newline_index == -1)
		return (v->line = *to_save, *to_save = NULL, v->line);
	v->line = ft_substr(*to_save, 0, v->newline_index + 1);
	if (!v->line)
		return (free_all(&v->temp_read, to_save), NULL);
	if ((*to_save)[v->newline_index + 1] != '\0')
	{
		v->start = &((*to_save)[v->newline_index + 1]);
		v->new_to_save = malloc((ft_strlen(v->start) + 1) * sizeof(char));
		if (!v->new_to_save)
			return (free_all(to_save, &v->line), NULL);
		ft_strlcpy_gnl(v->new_to_save, v->start, ft_strlen(v->start) + 1);
	}
	return (free_all(to_save, NULL), *to_save = v->new_to_save, v->line);
}

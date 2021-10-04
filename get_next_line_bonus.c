/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 02:44:27 by schetty           #+#    #+#             */
/*   Updated: 2021/07/05 21:29:58 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_str(char *s1, char *s2, size_t len)
{
	char	*tmp;
	char	*ptr;
	size_t	i;

	s2[len] = '\0';
	if (!s1)
		return (ft_strdup(s2));
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	ptr = s1;
	while (*ptr)
		tmp[i++] = *ptr++;
	ptr = s2;
	while (*ptr)
	{
		tmp[i++] = *ptr++;
	}
	tmp[i] = '\0';
	free(s1);
	return (tmp);
}

char	*has_newline(const char *s)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i] != '\n')
	{
		if (s[i] == '\0')
			return (NULL);
	}
	return ((char *)s + i);
}

char	*get_line(char **str)
{
	char	*is_new;
	char	*ret;
	char	*tmp;

	is_new = has_newline(*str);
	if (is_new)
	{
		ret = ft_substr(*str, 0, is_new - *str);
		if (!ret)
			return (NULL);
		tmp = *str;
		*str = ft_strdup(++is_new);
		if (!*str)
			return (NULL);
		free(tmp);
	}
	else
	{
		ret = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	return (ret);
}

int	get_buffer(int fd, char **str)
{
	char	*tmp;
	ssize_t	tmp_len;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (-1);
	tmp_len = BUFFER_SIZE;
	while (!has_newline(*str) && tmp_len == BUFFER_SIZE)
	{
		tmp_len = read(fd, tmp, BUFFER_SIZE);
		if (tmp_len < 0)
			break ;
		*str = join_str(*str, tmp, tmp_len);
		if (!*str)
			tmp_len = -1;
	}
	free(tmp);
	if (tmp_len < 0)
		return (-1);
	else if (has_newline(*str))
		return (1);
	else
		return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[OPEN_MAX];
	int			ret;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	ret = 1;
	if (!has_newline(str[fd]))
		ret = get_buffer(fd, &str[fd]);
	if (ret >= 0)
	{
		*line = get_line(&str[fd]);
		if (!*line)
			ret = -1;
	}
	return (ret);
}

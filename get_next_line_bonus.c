/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 02:44:27 by schetty           #+#    #+#             */
/*   Updated: 2021/12/26 06:07:28 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*join_str(char *s1, char *s2)
{
	char	*ret;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

static char	*get_current_line(char *str)
{
	char	*ret;
	int		i;

	if (!str[0])
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	ret = malloc(sizeof(char) * (i + 2));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		if (str[i++] == '\n')
			break ;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*clean_str(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	ret = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!ret)
		return (NULL);
	j = -1;
	while (str[++i])
		ret[++j] = str[i];
	ret[++j] = '\0';
	free(str);
	return (ret);
}

static char	*read_buffer(int fd, char *str)
{
	char	*buf;
	int		bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes = BUFFER_SIZE;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes != -1)
		{
			buf[bytes] = '\0';
			str = join_str(str, buf);
		}
	}
	free(buf);
	if (bytes == -1)
		return (NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*ret;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = read_buffer(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	ret = get_current_line(str[fd]);
	str[fd] = clean_str(str[fd]);
	return (ret);
}

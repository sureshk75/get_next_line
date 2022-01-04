/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 02:44:27 by schetty           #+#    #+#             */
/*   Updated: 2022/01/05 02:01:13 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char *str)
{
	char	*is_nl;

	if (!str[0])
		return (NULL);
	is_nl = ft_strchr(str, '\n');
	if (is_nl)
		return (ft_substr(str, 0, (ft_strlen(str) - ft_strlen(is_nl)) + 1));
	else
		return (ft_substr(str, 0, ft_strlen(str)));
}

static char	*clean_str(char *str)
{
	char	*ret;
	char	*is_nl;

	ret = NULL;
	is_nl = ft_strchr(str, '\n');
	if (is_nl && (is_nl[1]))
		ret = ft_substr(is_nl, 1, ft_strlen(is_nl) - 1);
	free(str);
	return (ret);
}

static char	*read_buffer(int fd, char *buf, char *str)
{
	int		bytes;
	char	*tmp;

	bytes = BUFFER_SIZE;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes != -1)
		{
			buf[bytes] = '\0';
			if (!str)
				str = ft_substr(buf, 0, ft_strlen(buf));
			else
			{
				tmp = ft_strjoin(str, buf);
				free(str);
				str = tmp;
			}
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
	char		*buf;
	char		*ret;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	str[fd] = read_buffer(fd, buf, str[fd]);
	if (!str[fd])
		return (NULL);
	ret = get_line(str[fd]);
	str[fd] = clean_str(str[fd]);
	return (ret);
}

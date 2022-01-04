/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 02:44:52 by schetty           #+#    #+#             */
/*   Updated: 2022/01/05 01:56:55 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i] != c)
	{
		if (!s[i])
			return (NULL);
	}
	return ((char *)s + i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ret)
		return (NULL);
	ret[s1_len + s2_len] = '\0';
	while (s2_len--)
		ret[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		ret[s1_len] = s1[s1_len];
	return (ret);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start > s_len)
		len = 0;
	else if (len > (s_len - start))
		len = s_len - start;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (++i < len + 1)
		dst[i] = 0;
	if (start < s_len)
	{
		while (len--)
			dst[len] = s[start + len];
	}
	return (dst);
}

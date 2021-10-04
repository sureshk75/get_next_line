/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 02:44:52 by schetty           #+#    #+#             */
/*   Updated: 2021/07/05 21:32:07 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (s[i])
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	ptr[i] = '\0';
	while (i--)
		ptr[i] = s[i];
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s)
		return (NULL);
	j = 0;
	while (s[j])
		j++;
	if (start > j)
		len = 0;
	else if (len > (j - start))
		len = j - start;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst)
	{
		if (len > 0)
		{
			i = -1;
			while (++i < len)
				dst[i] = s[start + i];
		}
		dst[len] = '\0';
	}
	return (dst);
}

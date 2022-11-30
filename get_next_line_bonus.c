/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:30:59 by aahrach           #+#    #+#             */
/*   Updated: 2022/11/21 13:09:09 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *buf, char **p)
{
	free(*p);
	*p = NULL;
	free(buf);
	return (NULL);
}

char	*ft_read(int fd, char **p, char *buf)
{
	char	*new;
	int		len;
	int		i;

	new = NULL;
	len = 1;
	while (len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
			return (ft_free(buf, p));
		buf[len] = '\0';
		*p = ft_strjoin(*p, buf);
		i = check_line(*p);
		if (i != -1)
		{
			new = ft_substr(*p, 0, i, 0);
			*p = ft_substr(*p, i + 1, ft_strlen(*p), 1);
			free (buf);
			return (new);
		}
	}
	new = ft_substr(*p, 0, ft_strlen(*p), 0);
	ft_free(buf, p);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*p[OPEN_MAX];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (NULL);
	return (ft_read(fd, &p[fd], buf));
}

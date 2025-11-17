/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahadda <adahadda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:14:56 by adahadda          #+#    #+#             */
/*   Updated: 2025/11/17 18:40:39 by adahadda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	char	cc;

	cc = (unsigned char) ch;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == cc)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}
char	*check_fail(int bytes_read, char **stash)
{
	char		*line_to_return;
		
	if (bytes_read == -1 || !*stash)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	else if (bytes_read == 0)
	{
		if(*(stash[0]) == '\0')
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		else
			{
				line_to_return = *stash;
				*stash = NULL;
				return (line_to_return);
			}
	}
	return ((char *)-1);
}
static void	join_to_stash(char **stash, char *buff)
{
	char	*temp_pointer;

	if (*stash == NULL)
		*stash = ft_strdup(buff);
	else
	{
		temp_pointer = *stash;
		*stash = ft_strjoin(*stash, buff);
		free(temp_pointer);
	}
}

char	*get_the_line(char **stash)
{
	size_t		total_len;
	char		*old_stash;
	char		*line_to_return;
	size_t		i;
	
	i = 0;
	while((*stash)[i] != '\n')
		i++;
	line_to_return = ft_substr(*stash, 0, i + 1);
	total_len = ft_strlen(*stash);
	old_stash = *stash;
	*stash = ft_substr(*stash, i + 1, (total_len - (i + 1)));
	free(old_stash);
	return (line_to_return);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*stash;
	int			bytes_read;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	do
	{
		bytes_read = read (fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)	
			break;
		buff[bytes_read] = '\0';
		join_to_stash(&stash, buff);
		if (stash == NULL)
			break;
	} while (!ft_strchr(stash, '\n'));
	free(buff);
	line = check_fail(bytes_read, &stash);
	if (line == (char *)-1)
		return (get_the_line(&stash));
	
	return (line);
}

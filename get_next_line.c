/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:04:28 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/07/08 08:57:55 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_kept_static(char *constant)
{
	int		i;
	int		j;
	char	*kept_static;

	i = 0;
	while (constant[i] && constant[i] != '\n')
		i++;
	if (!constant[i])
	{
		free(constant);
		return (NULL);
	}
	kept_static = (char *)malloc(sizeof(char) * (ft_strlen(constant) - i + 1));
	if (!kept_static)
		return (NULL);
	i++;
	j = 0;
	while (constant[i])
		kept_static[j++] = constant[i++];
	kept_static[j] = '\0';
	free(constant);
	return (kept_static);
}

char	*ft_reading_line(int fd, char *constant)
{
	char	*buf;
	int		bytes_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while ((!ft_strchr(buf, '\n') && bytes_read != 0))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		if (constant == NULL)
			constant = ft_strdup(buf);
		else
			constant = ft_strjoin(constant, buf);
	}
	free(buf);
	return (constant);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*constant;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	constant = ft_reading_line(fd, constant);
	if (!constant)
		return (NULL);
	line = ft_get_line(constant);
	constant = ft_kept_static(constant);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int    main(void)
{
    int    fd;
    char    *ret;

    fd = open("./test00", O_RDONLY);
    ret = get_next_line(fd);
    printf("%s", ret);
	free(ret);
	ret = get_next_line(fd);
    printf("%s", ret);
	free(ret);
	ret = get_next_line(fd);
    printf("%s", ret);
	free(ret);
	ret = get_next_line(fd);
    printf("%s", ret);
	free(ret);
	close(fd);
    return (0);
}
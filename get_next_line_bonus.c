/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 05:04:15 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/07/09 23:23:13 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	buf[0] = '\0';
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
	static char	*constant[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	constant[fd] = ft_reading_line(fd, constant[fd]);
	if (!constant[fd])
		return (NULL);
	line = ft_get_line(constant[fd]);
	constant[fd] = ft_kept_static(constant[fd]);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// int    main(void)
// {
//     int    fd;
//     char    *ret;

//     fd = open("./test00", O_RDONLY);
//     ret = get_next_line(fd);
//     printf("%s", ret);
// 	free(ret);
// 	ret = get_next_line(fd);
//     printf("%s", ret);
// 	free(ret);
// 	ret = get_next_line(fd);
//     printf("%s", ret);
// 	free(ret);
// 	ret = get_next_line(fd);
//     printf("%s", ret);
// 	free(ret);
// 	close(fd);
//     return (0);
// }
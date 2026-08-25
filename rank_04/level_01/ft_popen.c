/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 21:49:47 by brfialho          #+#    #+#             */
/*   Updated: 2026/08/24 22:38:34 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// int ft_popen(const char *file, char *const argv[], char type)
// {
	
// }

char	*get_next_line(int fd);

int main()
{
	{
		FILE *file;
		char *buffer;

		file = popen("ls", "r");
		buffer = malloc(1000);
		while (read(file->_fileno, buffer, 1000));
			printf("%s\n", buffer);
		free(buffer);
		pclose(file);
	}

	FILE *file;
	char buffer[1000];

	bzero(buffer, 1000);
	file = popen("bc", "w");
	while (read(1, buffer, 1000))
	{
		write(file->_fileno, buffer, strlen(buffer));
		bzero(buffer, 1000);
	}
	write(file->_fileno, "Hello World\n", 12);
	write(file->_fileno, "Olá Mundo\n", 11);
	pclose(file);
}

// int main()
// {
//     int  fd;
//     char *line;

//     fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     while ((line = get_next_line(fd)))
//         ft_putstr(line);
//     return (0);
// }


// int	main()
// {
//     int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     dup2(fd, 0);
//     fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
//     char    *line;
//     while ((line = get_next_line(fd)))
//                 printf("%s", line);
// }

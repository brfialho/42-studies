/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 21:49:47 by brfialho          #+#    #+#             */
/*   Updated: 2026/09/01 17:16:50 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	if (!file || !(type == 'w' || type == 'r'))
		return -1;

	int fd[2];
	int pid;

	type = (type == 'r');
	if (pipe(fd))
		return -1;
	if ((pid = fork()) == -1)
		return (close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
	{
		if (dup2(fd[type], type) == -1)
			exit(1);
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	return (close(fd[type]), fd[!type]);
}

int main()
{
	// {
	// 	FILE *file;
	// 	char *buffer;

	// 	file = popen("ls", "r");
	// 	buffer = malloc(1000);
	// 	while (read(file->_fileno, buffer, 1000));
	// 		printf("%s\n", buffer);
	// 	free(buffer);
	// 	pclose(file);
	// }

	// {
	// 	char *const argv[0] = NULL;
	// 	printf("%p\n", argv);
	// }

	// {
	// 	char	*b = calloc(2, 1);
	// 	b[0] = 'B';
	// 	char *const argv[2] = {"A", b};
	// 	printf("%p %ld\n", argv, sizeof(argv));
	// 	argv[1][0] = 'C';
	// 	printf ("%s\n", argv[1]);
	// 	free(b);
	// 	FILE *file;
	// }
	
	// char buffer[1000];
	// bzero(buffer, 1000);
	// file = popen("bc", "w");
	// while (read(0, buffer, 1000))
	// {
	// 	// write(file->_fileno, "Hello World\n", 12);
	// 	write(fileno(file), buffer, strlen(buffer));
	// 	bzero(buffer, 1000);
	// }
	// write(file->_fileno, "Hello World\n", 12);
	// write(file->_fileno, "Olá Mundo\n", 11);
	// pclose(file);

	{	
		int n;
		char buffer[100] = {0};
		int fd = ft_popen("cat", (char * const[]){"cat", "sandbox.c", NULL}, 'r');
		while ((n = read(fd, buffer, 100)))
		{
			write(1, buffer, n);
			bzero(buffer, 100);
		}
		close(fd);
	}

{	int n;
	char buffer[1000] = {0};
	int file = ft_popen("bc", (char * const[]){"bc", NULL}, 'w');
	while ((n = read(0, buffer, 1000)))
	{
		if (!strncmp(buffer, "END", 3))
			break;
		write(file, buffer, strlen(buffer));
		bzero(buffer, 1000);
	}
	close(file);}

		{	
		int n;
		char buffer[100] = {0};
		int fd = ft_popen("ls", (char * const[]){"ls", NULL}, 'r');
		dup2(fd, 0);
		close(fd);
		fd = ft_popen("grep", (char * const[]){"grep", "c", NULL}, 'r');
		while ((n = read(fd, buffer, 100)))
		{
			write(1, buffer, n);
			bzero(buffer, 100);
		}
		close(fd);
		close(0);
	}

	// char buffer[100] = {0};
	// while (read(1, buffer, 100))
	// {
	// 	printf("%s\n", buffer);
	// 	bzero(buffer, 100);
	// }

}



// int	main()
// {
//     int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     dup2(fd, 0);
//     fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
//     char    *line;
//     while ((line = get_next_line(fd)))
//                 printf("%s", line);
// }


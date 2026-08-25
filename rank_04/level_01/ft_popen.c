/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 21:49:47 by brfialho          #+#    #+#             */
/*   Updated: 2026/08/24 21:53:51 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
int ft_popen(const char *file, char *const argv[], char type)
{
	
}

int main()
{

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

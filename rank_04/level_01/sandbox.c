/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 20:14:42 by brfialho          #+#    #+#             */
/*   Updated: 2026/08/24 21:39:09 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

void segfault_function( void )
{
	char	*literal = "literal\n";

	literal[2] = '3';
}

void timeout_function( void )
{
	while (true);
}

void bad_exit_function( void )
{
	exit(1);
}

void good_function( void )
{
	char	*s = malloc(10);

	int i = -1;
	while (++i < 9)
		s[i] = 'b';
	s[i] = 0;
	printf("GOOD: %s\n", s);
	free(s);
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int	pid;
	int	exit_code;
	int	sig;

	if ((pid = fork()) == -1)
		return -1;
	else if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}
	waitpid(-1, &exit_code, 0);

	if (!verbose)
		return (!(exit_code == 0));
	if (WIFSIGNALED(exit_code))
	{
		(sig = WTERMSIG(exit_code)) == SIGALRM ? printf("Bad function: timed out after %d seconds\n", timeout)
		: printf("Bad function: %s\n", strsignal(sig));
		return 1;
	}
	if (exit_code == 0)
		printf("Nice function!\n");
	else
		printf("Bad function: exited with code %d\n", exit_code);
	return (!(exit_code == 0));
}

int main(void)
{
	printf("return value of good: %d\n", sandbox(good_function, 3, 1));
	printf("\n");
	printf("return value of segfault: %d\n", sandbox(segfault_function, 3, 1));
	printf("\n");
	printf("return value of bad_exit: %d\n", sandbox(bad_exit_function, 3, 1));
	printf("\n");
	printf("return value of timeout: %d\n", sandbox(timeout_function, 3, 1));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaksi <klaksi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:54:19 by klaksi            #+#    #+#             */
/*   Updated: 2023/05/02 17:54:04 by klaksi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int	main(void)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*buff;

	buff = malloc(3 * sizeof(char));
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		write(pipe_fd[1], "lol", 3);
		close(pipe_fd[1]);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(pipe_fd[1]);
		read(pipe_fd[0], buff, 3);
		close(pipe_fd[0]);
		printf("pipe: %s\n", buff);
	}
	return (0);
}

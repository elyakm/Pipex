/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaksi <klaksi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:54:19 by klaksi            #+#    #+#             */
/*   Updated: 2023/05/08 16:28:33 by klaksi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int	main()
{
	pid_t	pid;
	int		pipefd[2];
	char	*buff;

	buff = malloc(8 * sizeof (char));
	pipe(pipefd);
	pid = fork();
	if (pid == 0) // child
	{
		close(pipefd[0]); //close fd pour lire
		write(pipefd[1], "kskonveu", 8); //write
		close(pipefd[1]); // close fd pour ecrire
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		read(pipefd[0], buff, 8);
		printf("result : %s\n", buff);
		close(pipefd[0]);
	}
	return (0);
}
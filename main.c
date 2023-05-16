/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaksi <klaksi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:06:31 by klaksi            #+#    #+#             */
/*   Updated: 2023/05/16 16:56:11 by klaksi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft/include/libft.h"

int main(int argc, char **argv, char **envp)
{
    pid_t   pid1;
    pid_t   pid2;
    int     pipefd[2];
    int     fd1;
    int     fd2;
    char    **env;
    int     i;
    char    **cmd1;
    char    **cmd2;

    cmd1 = ft_split(argv[2], ' ');
    cmd2 = ft_split(argv[3], ' ');
    i = 0;
    while (envp[i])
    {
        if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
        {
            env = ft_split(ft_strtrim(envp[i], "PATH="), ':');
            break ;
        }
        i++;
    }
    i = 0;
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    pipe(pipefd);
    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipefd[0]);
        dup2(fd1, STDIN_FILENO);
        close(fd1);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        i = 0;
        while (env[i])
        {
            if (access(ft_strjoin(env[i], ft_strjoin("/", cmd1[0])), X_OK | F_OK | R_OK) != -1)
                execve(ft_strjoin(env[i], ft_strjoin("/", cmd1[0])), cmd1, envp);
            i++;
        }
    }
    waitpid(pid1, NULL, 0);
    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        dup2(fd2, STDOUT_FILENO);
        i = 0;
        while (env[i])
        {
            if (access(ft_strjoin(env[i], ft_strjoin("/", cmd2[0])), X_OK) != -1)
                execve(ft_strjoin(env[i], ft_strjoin("/", cmd2[0])), cmd2, envp);
            i++;
        }
    }
    return (0);
}

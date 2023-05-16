/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaksi <klaksi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:52:49 by klaksi            #+#    #+#             */
/*   Updated: 2023/05/16 18:56:31 by klaksi           ###   ########.fr       */
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
    int     count_pipe; //pour compter le nbr de pipes
    int     count_cmd; //pour compter le nbr de cmds
    char    ***cmd_arr; // contient toutes les cmds sous forme d'array  ( [ ["cat", "-l", NULL], ["ls", "-a", NULL] ] )
    int     **pipefd; //array des pipes
    char    **env; // path qu'on a split et trim pour avoir les paths pour les cmds
    int     fd_infile;
    int     fd_outfile;
    pid_t   pid; //processus ID. Pour fork et creer un child process
    int     i;
    int     j;

    count_cmd = argc - 3;
    count_pipe = argc - 4; // ou count_pipe = count_cmd - 1 car ya tjrs un pipe de moins que le nbr de cmds

    // malloc cmd_arr --------------------------------------

    cmd_arr = malloc (count_cmd * sizeof(char **) + 1);
    ft_printf("hii1\n");
    // loop pour rentrer les cmds splittées dans cmd_arr
    i = 0;
    while(i < count_cmd)
    {
        ft_printf("hii2\n");
        cmd_arr[i] = ft_split(argv[i + 2], ' '); // split argv at i+2(cmd1 (i+0:a.out, i+1:infile, i+2:cmd1)) and store the result in cmd_arr at index i
        i++;
    }
    ft_printf("hii3\n");
    i = 0;
    ft_printf("hii4\n");
    while (cmd_arr[i])
    {
         ft_printf("hii5\n");
        j = 0;
        while (cmd_arr[i][j])
        {
            ft_printf("%s\n", cmd_arr[i][j]);
            j++;
        }
        i++;
    }

}
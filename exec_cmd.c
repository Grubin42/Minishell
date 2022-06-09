/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:17 by grubin            #+#    #+#             */
/*   Updated: 2022/06/09 11:08:01 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pipe(t_data *data)
{
    int i;
    int j;
    int fd[data->nbr_cmd - 1][2];
    int pid_child;
    
    i = 0;
    j = 0;
    while (i < data->nbr_cmd - 1)
    {
        pipe(fd[i]);
        i++;
    }
    i = 0;
    while (i <= data->nbr_cmd - 1)
    {
        pid_child = fork();
        if(pid_child == 0)
        {
            if (i > 0)
                dup2(fd[i - 1][0], STDIN_FILENO); 
            if (i < data->nbr_cmd - 1)
                dup2(fd[i][1], STDOUT_FILENO);    
            while(j < data->nbr_cmd - 1)
            {
                close(fd[j][0]);
                close(fd[j][1]);
                j++;
            }
            j = 0;
            ft_builtins_with_pipe(data, i);
        }
        i++;     
    }
    while(j < data->nbr_cmd - 1)
    {
        close(fd[j][0]);
        close(fd[j][1]);
        j++;
    }
    j = 0;
    waitpid(pid_child, NULL, 0);
    return (0);
}

int ft_exec_cmds(t_data *data)
{
    if (data->nbr_cmd == 1)
        ft_builtins_without_pipe(data);
    else
        ft_pipe(data);
    return (0);
}
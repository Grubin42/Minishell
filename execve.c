/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:39:13 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/20 15:14:25 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_execve(t_data *data)
{
    int     i;
    char    *cmd;
    char    *cmd_path;
    
    data->str_getenv = ft_getenv(data, "PATH");
    data->tab_getenv = ft_split(data->str_getenv, ':');//free
    i = 0;
    while (data->tab_getenv[i])
    {
        cmd_path = ft_join(data->tab_getenv[i], "/");//free
        cmd = ft_join(cmd_path, data->tab_cpy[0]);//free
        free(cmd_path);
        if (access(cmd, X_OK) == 0)
            execve(cmd, data->tab_cpy, NULL);
        free(cmd);
        i++;
    }
    printf("$: %s: command not found\n", data->tab_cpy[0]);
    exit(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:39:13 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:04 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_execve(t_data *data, int i_cmd)
{
    int     i;
    char    *cmd;
    char    *cmd_path;
    
    data->str_getenv = getenv("PATH");
    data->tab_getenv = ft_split(data->str_getenv, ':');//free
    i = 0;
    while (data->tab_getenv[i])
    {
        //faire copie data.tab_cmd
        //utiliser la copie dans le reste de la fonction
        //free tab
        cmd_path = ft_join(data->tab_getenv[i], "/");//free
        cmd = ft_join(cmd_path, data->tab_cmd[i_cmd].args[0]);//free
        free(cmd_path);
        if (execve(cmd, &data->tab_cmd[i_cmd].args[0], NULL) == - 1)
        {
            printf("$ %s: command not found\n", data->tab_cmd[i_cmd].args[0]);
            break ;
        }
        free(cmd);
        i++;
    }
    exit(0);
}
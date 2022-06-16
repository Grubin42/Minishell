/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:39:13 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/16 13:59:42 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_lol(t_data *data, int i_cmd, int i_arg, int i)
{
    while (data->tab_cmd[i_cmd].args[i_arg])
    {
        if ((ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], ">\0", 2) == 0
            && data->tab_cmd[i_cmd].args[i_arg + 1])
            ||(ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], "<\0", 2) == 0
            && data->tab_cmd[i_cmd].args[i_arg + 1]) 
            || (ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], ">>\0", 3) == 0
            && data->tab_cmd[i_cmd].args[i_arg + 1])
            ||(ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], "<<\0", 3) == 0
            && data->tab_cmd[i_cmd].args[i_arg + 1]) )
            i_arg += 2;
        else if (ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], ">\0", 2) == 0
            || ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], "<\0", 2) == 0
            || ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], ">>\0", 2) == 0
            || ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], "<<\0", 2) == 0)
            i_arg++;
        else
        {
            data->tab_cpy[i] = ft_strdup(data->tab_cmd[i_cmd].args[i_arg]);
            i++;
            i_arg++;
        }
    }
    data->tab_cpy[i] = NULL;
}

void ft_tabcpy(t_data *data, int i_cmd, int i_arg)
{
    int len;
    int i;

    i = 0;
    len = ft_count_args(data, i_cmd);
    data->tab_cpy = ft_calloc(len + 1, sizeof(char*));
    ft_lol(data, i_cmd, i_arg, i);
}

int ft_execve(t_data *data, int i_cmd)
{
    int     i;
    char    *cmd;
    char    *cmd_path;
    
    data->str_getenv = ft_getenv(data, "PATH");
    data->tab_getenv = ft_split(data->str_getenv, ':');//free
    i = 0;
    while (data->tab_getenv[i])
    {
        ft_tabcpy(data, i_cmd, 0);
        cmd_path = ft_join(data->tab_getenv[i], "/");//free
        cmd = ft_join(cmd_path, data->tab_cpy[0]);//free
        free(cmd_path);
        if (access(cmd, X_OK) == 0)
            execve(cmd, &data->tab_cpy[0], NULL);
        ft_free_tab(data->tab_cpy);
        free(cmd);
        i++;
    }
    printf("$: %s: command not found\n", data->tab_cmd[i_cmd].args[0]);
    exit(0);
}
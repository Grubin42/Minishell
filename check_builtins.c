/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:54:59 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/07 12:01:27 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_builtins(t_data *data, int i)
{
    if (data->tab_cmd[i].args[0] == NULL)
        return (0);
    if (ft_strncmp(data->tab_cmd[i].args[0], "echo\0", 5) == 0)
    {
        ft_echo(data, i);
        //printf("machin =%s\n", data->tab_cmd[i].args[0]);
    }
    else if (ft_strncmp(data->tab_cmd[i].args[0], "cd\0", 3) == 0)
    {
        ft_cd(data, i);
    }
    else if (ft_strncmp(data->tab_cmd[i].args[0], "pwd\0", 4) == 0)
    {    
       ft_pwd();
       //printf("sasa\n");
    }
    else if (ft_strncmp(data->tab_cmd[i].args[0], "export\0", 7) == 0)
    {
        printf("machin =%s\n", data->tab_cmd[i].args[0]);
    }
    else if (ft_strncmp(data->tab_cmd[i].args[0], "unset\0", 6) == 0)
    {
        printf("machin =%s\n", data->tab_cmd[i].args[0]);
    }
    else if (ft_strncmp(data->tab_cmd[i].args[0], "env\0", 4) == 0)
    {
        ft_env(data);
        //printf()
    }
    else if (ft_strncmp(data->tab_cmd[i].args[0], "exit\0", 5) == 0)
    {
        ft_exit();
        printf("machin =%s\n", data->tab_cmd[i].args[0]);
    }
    else
    {
        ft_execve(data, i);
    }
    return (0);
}
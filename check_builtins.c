/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:54:59 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/16 15:55:50 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_egal(char *str)
{
    int i;

    i = 0;
    while (str[i] != '=')
        i++;
    return (i + 1);
}

int ft_envcmp(t_data *data, int i_cmd)
{
    char *tmp;
    int i;

    i = 0;
    tmp = ft_calloc(1024, sizeof(char));
    while (data->envp[i])
    {
        ft_strcpy(tmp, &data->envp[i][ft_egal(data->envp[i])]);
        if (ft_strncmp(data->tab_cmd[i_cmd].args[0], tmp, ft_strlen(data->tab_cmd[i_cmd].args[0])) == 0)
        {
            free(tmp);
            return (0);
        }
        else
            ft_bzero(tmp, ft_strlen(tmp));
        i++;
    }
    free(tmp);
    return (1);
}

int ft_builtins_with_pipe(t_data *data, int i)
{
    if (data->tab_cmd[i].args[0] == NULL)
        return (0);
    if (ft_strncmp(data->tab_cmd[i].args[0], "echo\0", 5) == 0)
        ft_echo(data, 0);
    else if (ft_strncmp(data->tab_cmd[i].args[0], "cd\0", 3) == 0)
        ft_cd(data, 0);
    else if (ft_strncmp(data->tab_cmd[i].args[0], "pwd\0", 4) == 0)
        ft_pwd(data);
    else if (ft_strncmp(data->tab_cmd[i].args[0], "export\0", 7) == 0)
        ft_export(data);
    else if (ft_strncmp(data->tab_cmd[i].args[0], "unset\0", 6) == 0)
        ft_unset(data);
    else if (ft_strncmp(data->tab_cmd[i].args[0], "env\0", 4) == 0)
        ft_env(data);
    else if (ft_envcmp(data, i) == 0 && ft_count_args(data, i) == 1)
        printf("%s\n", data->tab_cmd[i].args[0]);
    else
        ft_execve(data, i);
    exit(0);
}

int ft_builtins_without_pipe(t_data *data)
{
    if (data->tab_cmd[0].args[0] == NULL)
        return (0);
    if (ft_strncmp(data->tab_cmd[0].args[0], "echo\0", 5) == 0)
        ft_echo(data, 0);
    else if (ft_strncmp(data->tab_cmd[0].args[0], "cd\0", 3) == 0)
        ft_cd(data, 0);
    else if (ft_strncmp(data->tab_cmd[0].args[0], "pwd\0", 4) == 0)
       ft_pwd(data);
    else if (ft_strncmp(data->tab_cmd[0].args[0], "export\0", 7) == 0)
        ft_export(data);
    else if (ft_strncmp(data->tab_cmd[0].args[0], "unset\0", 6) == 0)
        ft_unset(data);
    else if (ft_strncmp(data->tab_cmd[0].args[0], "env\0", 4) == 0)
        ft_env(data);
    else if (ft_envcmp(data, 0) == 0 && ft_count_args(data, 0) == 1)
        printf("%s\n", data->tab_cmd[0].args[0]);
    else
        ft_execve(data, 0);
    return (0);
}
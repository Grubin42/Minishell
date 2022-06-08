/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:57:27 by grubin            #+#    #+#             */
/*   Updated: 2022/06/07 16:00:47 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_args(t_data *data, int i_cmd)
{
    int i_args;
    int count;
    
    i_args = 0;
    count = 0;
    while (data->tab_cmd[i_cmd].args[i_args])
    {
        i_args++;
        count++;
    }
    return (count);
}

void ft_init_path_home(t_cd *cd)
{
    char *tmp;
    
    tmp = ft_strdup(getenv("HOME"));
    cd->path = ft_strjoin(cd->path, tmp);
    free(tmp);
}

void    ft_init_path_cd(t_cd *cd, t_data *data, int i_cmd)
{   
    if (ft_count_args(data, i_cmd) == 2)
    {
        if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "~", 1) == 0)
            ft_init_path_home(cd);
        else if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "-", 1) == 0)
            cd->path = ft_strcpy(cd->path, cd->oldpwd);
        else
        {
            cd->path = ft_strcpy(cd->path, cd->pwd);
            cd->path = ft_strjoin(cd->path, "/");
            cd->path = ft_strjoin(cd->path, data->tab_cmd[i_cmd].args[1]);
        }
    }
}

int ft_init_cd_struct(t_cd *cd, t_data *data, int i_cmd)
{
    cd->path = ft_calloc(1024, sizeof(char));
    cd->pwd = ft_strdup(getenv("PWD"));
    cd->oldpwd = ft_strdup(getenv("OLDPWD"));
    if (ft_count_args(data, i_cmd) == 2)
        ft_init_path_cd(cd, data, i_cmd);
    else
        ft_init_path_home(cd);
    return (0);
}

void    ft_free_cd(t_cd *cd)
{
    free(cd->oldpwd);
    free(cd->path);
    free(cd->pwd);
}

int ft_change_envp(t_cd *cd, t_data *data)
{
    int i;
    char *tmp;
    
    i = 0;
    while (data->envp[i])
    {
        if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
        {
            tmp = ft_calloc(1024, sizeof(char));
            tmp = ft_strjoin(tmp, "PWD=");
            tmp = ft_strjoin(tmp, cd->path);
            ft_bzero(data->envp[i], ft_strlen(data->envp[i]));
            data->envp[i] = ft_join(tmp, "\0");
            free(tmp);
            tmp = ft_calloc(1024, sizeof(char));
            tmp = ft_strjoin(tmp, "OLDPWD=");
            tmp = ft_strjoin(tmp, cd->pwd);
            ft_bzero(data->envp[i + 1], ft_strlen(data->envp[i + 1]));
            data->envp[i + 1] = ft_join(tmp, "\0");
            free(tmp);
        }
        i++;
    }
    ft_free_cd(cd);
    return (0);
}

void ft_go_change_envp(t_cd *cd, t_data *data, int i_cmd)
{
    int res;
    
    res = 0;        
    if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "..",2) == 0)
    {
        //ft_init_cd_struct(cd , data, i_cmd);
    }
    else if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "-", 1) == 0)
    {
        ft_init_cd_struct(cd , data, i_cmd);
        printf("%s\n", cd->oldpwd);
    }
    else
        ft_init_cd_struct(cd , data, i_cmd);
    res = chdir(cd->path);
    if (res == 0)
        ft_change_envp(cd, data);
    else
    {
        printf("cd: no such file or directory: %s\n", data->tab_cmd[i_cmd].args[1]);
        ft_free_cd(cd);
    }
}

int ft_cd(t_data *data, int i_cmd)
{
    t_cd cd;

    if (ft_count_args(data, i_cmd) <= 2)
        ft_go_change_envp(&cd, data, i_cmd);
    else
        printf("cd: string not in pwd: %s\n", data->tab_cmd[i_cmd].args[1]);
    return (0);
}
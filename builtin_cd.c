/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:57:27 by grubin            #+#    #+#             */
/*   Updated: 2022/06/09 15:06:03 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_init_cd_with_args(t_cd *cd, t_data *data, int i_cmd)
{
    cd->path = ft_calloc(1024, sizeof(char));
    cd->pwd = ft_strdup(getenv("PWD"));
    cd->oldpwd = ft_strdup(getenv("OLDPWD"));
    if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "~", 1) == 0)
        cd->path = ft_strdup(getenv("HOME"));
    else if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "-", 1) == 0)
    {
        cd->path = ft_strcpy(cd->path, cd->oldpwd);
        printf("%s\n", cd->oldpwd);
    }
    //else if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "..", 1) == 0)
        //ft_go_up_the_path(cd, data);
    else
    {
        cd->path = ft_strcpy(cd->path, cd->pwd);
        cd->path = ft_strjoin(cd->path, "/");
        cd->path = ft_strjoin(cd->path, data->tab_cmd[i_cmd].args[1]);
    }
    return (0);
}

int ft_init_cd_without_args(t_cd *cd)
{
    cd->path = ft_strdup(getenv("HOME"));
    cd->pwd = ft_strdup(getenv("PWD"));
    cd->oldpwd = ft_strdup(getenv("OLDPWD"));
    return (0);
}

int ft_execute_order_sixty_six(t_cd *cd, t_data *data, int i)
{
    char *tmp;
    char *tmp_env;

    tmp = ft_calloc(1024, sizeof(char));
    tmp = ft_strjoin(tmp, "PWD=");
    tmp = ft_strjoin(tmp, cd->path);
    ft_bzero(data->envp[i], ft_strlen(data->envp[i]));
    tmp_env = ft_join(tmp, "\0");
    ft_strcpy(data->envp[i], tmp_env);
    free(tmp_env);
    free(tmp);
    tmp = ft_calloc(1024, sizeof(char));
    tmp = ft_strjoin(tmp, "OLDPWD=");
    tmp = ft_strjoin(tmp, cd->pwd);
    ft_bzero(data->envp[i + 1], ft_strlen(data->envp[i + 1]));
    tmp_env = ft_join(tmp, "\0");
    ft_strcpy(data->envp[i + 1], tmp_env);
    free(tmp_env);
    free(tmp);
    return (0);
}

int ft_change_envp(t_cd *cd, t_data *data)
{
    int i;

    i = 0;
    while (data->envp[i])
    {
        if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
            ft_execute_order_sixty_six(cd, data, i);
        i++;
    }
    ft_free_cd(cd);
    return (0);
}

int ft_cd(t_data *data, int i_cmd)
{
    t_cd cd;
    
    if (ft_count_args(data, i_cmd) == 2)
    {
        ft_init_cd_with_args(&cd, data, i_cmd);
        ft_chdir(&cd, data, i_cmd);
    }
    else if (ft_count_args(data, i_cmd) == 1)
    {
        ft_init_cd_without_args(&cd);
        ft_chdir(&cd, data, i_cmd);
    }
    else
        printf("cd: string not in pwd: %s\n", data->tab_cmd[i_cmd].args[1]);
    return (0);
}
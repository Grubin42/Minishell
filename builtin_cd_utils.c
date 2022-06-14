/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:48:39 by grubin            #+#    #+#             */
/*   Updated: 2022/06/14 10:05:28 by grubin           ###   ########.fr       */
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

void    ft_free_cd(t_cd *cd)
{
    free(cd->oldpwd);
    free(cd->path);
    free(cd->pwd);
}

int ft_chdir(t_cd *cd, t_data *data, int i_cmd)
{
    int res;

    res = chdir(cd->path);
    if (res == 0) 
        ft_change_envp(cd, data);
    else
    {
        printf("cd: no such file or directory: %s\n", data->tab_cmd[i_cmd].args[1]);
        ft_free_cd(cd);
    }
    return (0);
}


int ft_go_up_the_path(t_cd *cd, t_data *data)
{
    int i;
    int count;
    char **tab;

    i = 0;
    count = 0;
    tab = ft_split(data->tab_cmd[0].args[1], '/');
    cd->path = NULL;
    while (tab[i])
    {
        if (strncmp(tab[i], "..\0", 3) == 0)
            count++;
        i++;
    }
    ft_free_tab(tab);
    
    return (0);
}


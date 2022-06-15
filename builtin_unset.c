/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 08:54:11 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/15 10:17:03 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_init_struct_unset(t_unset *unset, t_data *data)
{
    int i;

    i = 0;
    while (data->envp[i])
        i++;
    unset->tab = ft_calloc(i + 1 , sizeof(char*));
    unset->tab[i] = NULL;
    return (0);
}

int ft_realloc_envp_unset(t_data *data, t_unset *unset)
{
    int i;

    i = 0;
    while (unset->tab[i])
        i++;
    data->envp = ft_calloc(i + 1, sizeof(char*));
    if (!data->envp)
        return (0);
    i = 0;
    while(unset->tab[i])
    {
        data->envp[i] = ft_strdup(unset->tab[i]);
        i++;
    }
    data->envp[i] = NULL;
    ft_free_tab(unset->tab);
    return (i);
}

int ft_new_tab_unset(t_data *data, t_unset *unset, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(data->envp[i])
    {
        if(ft_strncmp(str, data->envp[i], ft_count_egale(data->envp[i])) != 0)
        {
            unset->tab[j] = ft_strdup(data->envp[i]);
            j++;
        }
        i++;
    }
    ft_free_tab(data->envp);
    ft_realloc_envp_unset(data, unset);
    return (0);
}

int ft_unset(t_data *data)
{
    int i;
    int j;
    int k;
    t_unset unset;
    char *str;

    i = 0;
    j = 0;
    k = 1;
    if (ft_count_args(data, 0) == 1)
        return (0);
    while(data->tab_cmd[0].args[k])
    {
        ft_init_struct_unset(&unset, data);
        str = ft_calloc(ft_strlen(data->tab_cmd[0].args[k]) + 2, sizeof(char));
        ft_strjoin(str, data->tab_cmd[0].args[k]);
        ft_strjoin(str, "=");
        ft_new_tab_unset(data, &unset, str);
        free(str);
        k++;
    }
    return (0);
}





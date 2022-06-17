/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 08:54:11 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/17 15:10:41 by grubin           ###   ########.fr       */
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

int ft_new_tab_unset(t_data *data, char *arg, t_unset *unset)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(data->envp[i])
    {
        if(ft_strncmp(arg, data->envp[i], ft_strlen(arg)) != 0)
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
    t_unset unset;

    i = 1;
    if (ft_count_args(data, 0) == 1)
        return (0);
    while(data->tab_cmd[0].args[i])
    {
        if (data->tab_cmd[0].args[i][ft_strlen(data->tab_cmd[0].args[i]) - 1] != '=')
        {
            ft_init_struct_unset(&unset, data);
            ft_new_tab_unset(data, data->tab_cmd[0].args[i], &unset);
            i++;
        }
        else
        {
            printf("$: unset: `%s': not a valid identifier\n", data->tab_cmd[0].args[i]);
            i++;
        }
    }
    return (0);
}
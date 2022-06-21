/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:23:05 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/21 15:26:11 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_data *data, char **tab)
{
    int i;

    i = 0;
    if (tab[1])
    {    
        printf("env: %s: No such file or directory\n", data->tab_cmd[0].args[1]);
        return (0);
    }
    while (data->envp[i])
    {
        printf("%s\n", data->envp[i]);
        i++;
    }
    return (0);
}
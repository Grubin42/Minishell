/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:21:52 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/16 14:56:41 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_data *data , int i_cmd)
{
    int i_arg;

    i_arg = 1;
    while(data->tab_cmd[i_cmd].args[i_arg])
    {
        if (ft_strncmp(data->tab_cmd[i_cmd].args[i_arg], "-n\0", 3) == 0)
            i_arg++;
        printf("%s", data->tab_cmd[i_cmd].args[i_arg]);
        if (data->tab_cmd[i_cmd].args[i_arg + 1])
          printf(" ");  
        i_arg++;
    }
    if (ft_strncmp(data->tab_cmd[i_cmd].args[1], "-n\0", 3) == 0)
        return (0);
    else
        printf("\n");
    return (0);
}
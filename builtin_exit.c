/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:22:22 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/15 09:04:00 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit_prog(t_data *data)
{
    int i_cmd;

    i_cmd = 0;
    if (!data->tab_cmd[0].args[0])
        return (0);
    while(i_cmd < data->nbr_cmd)
    {
        if (ft_strncmp(data->tab_cmd[0].args[0], "exit\0", 5) == 0)
           exit (0); 
        else if (ft_strncmp(data->tab_cmd[data->nbr_cmd - 1].args[0], "exit\0", 5) == 0)
            exit(0);
        else
            i_cmd++;
    }
    return (0);
}
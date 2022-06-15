/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:21:52 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/15 10:38:13 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_data *data , int i_cmd)
{
    int i_arg;

    i_arg = 1;
    while(data->tab_cmd[i_cmd].args[i_arg])
    {
        printf("%s ", data->tab_cmd[i_cmd].args[i_arg]);
        i_arg++;
    }
    printf("\n");
    //exit (0);
    return (0);
}
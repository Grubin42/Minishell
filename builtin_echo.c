/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:21:52 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/20 15:22:16 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_data *data)
{
    int i_arg;

    i_arg = 1;
    while(data->tab_cpy[i_arg])
    {
        if (ft_strncmp(data->tab_cpy[i_arg], "-n\0", 3) == 0)
            i_arg++;
        printf("%s", data->tab_cpy[i_arg]);
        if (data->tab_cpy[i_arg + 1])
          printf(" ");  
        i_arg++;
    }
    if (ft_strncmp(data->tab_cpy[1], "-n\0", 3) == 0)
        return (0);
    else
        printf("\n");
    return (0);
}
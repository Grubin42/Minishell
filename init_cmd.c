/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:47:29 by grubin            #+#    #+#             */
/*   Updated: 2022/04/28 16:55:30 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_malloc_tab_args(t_data *data)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (data->tab_chunck[i])
    {
        if (data->tab_chunck[i][0] == '|')
            count++;
        i++;
    }
    data->tab_args = ft_calloc((count + 2), sizeof(t_cmd));
    return (0);
}

int ft_count_token(t_data *data)
{
    int i;

    i = 0;
    while (data->tab_chunck[i])
        i++;
    return (i);
}

int ft_init_tab_args(t_data *data, int count)
{
    int i_chunk;
    int i_arg;
    int i_cmd;

    i_chunk = - 1;
    i_cmd = 0;
    i_arg = 0;
    while (data->tab_chunck[++i_chunk])
    {
        if (data->tab_chunck[i_chunk][0] == '|')
        {
            i_arg = 0;
            i_cmd++;
            data->tab_args[i_cmd].args = ft_calloc(count + 1, sizeof(char*));
        }
        else
        {
            data->tab_args[i_cmd].args[i_arg] = data->tab_chunck[i_chunk]; 
            i_arg++;
        }
    }
    return (0);
}

int ft_init_cmd(t_data *data)
{
    int count;
    
    ft_malloc_tab_args(data);
    count = ft_count_token(data);
    data->tab_args[0].args = ft_calloc(count + 1, sizeof(char*));
    ft_init_tab_args(data, count);
    return (0);
}
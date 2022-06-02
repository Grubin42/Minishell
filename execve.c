/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschreye <jschreye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:39:13 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/02 16:32:25 by jschreye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_execve(t_data *data, int i_cmd)
{
    int     i;
    char    *cmd;
    char    *cmd_path;
    
    data->str_getenv = getenv("PATH");
    data->tab_getenv = ft_split(data->str_getenv, ':');//free
    i = 0;
    while (data->tab_getenv[i])
    {
        cmd_path = ft_strjoin(data->tab_getenv[i], "/");//free
        cmd = ft_strjoin(cmd_path, data->tab_cmd[i_cmd].args[0]);//free
        execve(cmd, &data->tab_cmd[i_cmd].args[0], NULL);
        i++;
    }
    exit(0);
}
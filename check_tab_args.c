/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschreye <jschreye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:17 by grubin            #+#    #+#             */
/*   Updated: 2022/05/24 13:44:17 by jschreye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_input_redirect(t_data *data, int i)
{

}

int ft_exec_output_redirect(t_data *data, int i)
{

}

int ft_exec_cmd_tab(t_data *data, int is_a_pipe, int i)
{
    //int res;
    is_a_pipe = 0;
    int saved_stdin;
    int saved_stdout;
    
    saved_stdin = ft_exec_input_redirect(data, i);
    if (data->tab_cmd[i].input_fd == -2)
       return (-1);
    saved_stdout = ft_exec_output_redirect(data , i);
    ft_access_path(data);
    if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
    return (0);
}

int ft_check_tab_args(t_data *data)
{
    int p[2];
    int is_a_pipe;
    int i;

    i = 0;
    while (i < data->size_cmd)
    {
        if (data->size_cmd > 1)
        {
            is_a_pipe = 1;
            pipe(p);
            data->tab_cmd[i].output_fd = p[1];
            data->tab_cmd[i + 1].input_fd = p[0];
        }
        ft_exec_cmd_tab(data, is_a_pipe, i);
        if (data->tab_cmd[i].output_fd >= 0)
            close(data->tab_cmd[i].output_fd);
        if (data->tab_cmd[i].input_fd >= 0)
            close(data->tab_cmd[i].input_fd);
        i++;       
    }
    return (0);
}
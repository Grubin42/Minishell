/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:17 by grubin            #+#    #+#             */
/*   Updated: 2022/06/20 15:14:33 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_init_red(t_fd *files)
{
    files->append = 0;
    files->fd_in = -1;
    files->fd_out = -1;
    files->heredocs = 0;
    files->red = 0;
}

int ft_exec_child(t_data *data, int fd[data->nbr_cmd - 1][2], int i, t_fd *files)
{
    if (i > 0)
        dup2(fd[i - 1][0], STDIN_FILENO);
    if (i < data->nbr_cmd - 1)
        dup2(fd[i][1], STDOUT_FILENO); 
    close_pipes(data->nbr_cmd - 1, fd);
    if (files->red == 1)
        exec_red(data, files, i);
    else if (files->red == 0)
        ft_builtins_with_pipe(data, i);
    return (0);   
}

int ft_init_fd(t_data *data, t_fd *files, int i)
{
    ft_init_red(files);
    error_red(data->tab_cmd[i].args, files, i);
    ft_check_fd_in(data->tab_cmd[i].args, files);
    ft_tabcpy(data, i, 0);
    return (0);
}

int ft_pipe(t_data *data)
{
    t_fd    files;
    int     i;
    int     fd[data->nbr_cmd-1][2];
    int     pid;
   
    i = 0;
    while (i < data->nbr_cmd-1)
    {
        pipe(fd[i]);
        i++;
    }
    i = 0;
    while (i <= data->nbr_cmd-1)
    {
        pid = fork();
        if (pid == 0)
        {
            ft_init_fd(data, &files, i);
            ft_exec_child(data, fd, i, &files);
            ft_free_tab(data->tab_cpy);
            close_pipes(data->nbr_cmd-1, fd);
            exit(0);
        }
        i++;
    }
    close_pipes(data->nbr_cmd-1, fd);
    waitpid(pid, NULL, 0);
    return (0);
}

int ft_exec_cmds(t_data *data)
{
    char *tmp;

    tmp = "|\0";
    if (ft_del_quote(data) == 1)
        return (0);
    if (ft_exit_prog(data) == 1)
        return (1);
    if (data->nbr_cmd == 2 && ft_strncmp(data->tab_chunck[0], tmp, 2) == 0)
    {
        printf("$: syntax error near unexpected token `|'\n");
        return (0);
    }
    ft_pipe(data);
    return (0);
}
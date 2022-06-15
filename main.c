/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:05:12 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/15 09:03:55 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(t_data *data, char *str)
{
    char *new_str;
    int i;

    i = 0;
    while (data->envp[i])
    {
        if (ft_strncmp(data->envp[i], str, ft_strlen(str)) == 0)
        {
            new_str = ft_calloc(ft_strlen(data->envp[i]) + ft_strlen(str), sizeof(char));
            new_str = ft_strcpy(new_str, &data->envp[i][ft_strlen(str) + 1]);
            return (new_str);
        }
        i++;
    }
    return (NULL);
}

void ft_print_tab(char **tab)
{
    int i = 0;

    while (tab[i])
    {
        printf("tab = %s\n", tab[i]);
        i++;
    }
}

void ft_free_tab(char  **tab)
{
    int i;

    i = 0;
    while(tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void    ft_free_cd(t_cd *cd)
{
    free(cd->oldpwd);
    free(cd->path);
    free(cd->pwd);
}

void ft_free(t_data *data)
{
    int i;

    i = 0;
    if (data->str_rl)
        free(data->str_rl);
    if (data->str_chunk)
        free(data->str_chunk);
    i = 0;
    while (data->tab_chunck[i])
    {
        free(data->tab_chunck[i]);
        i++;
    }
    free(data->tab_chunck);
    i = 0;
    while (data->tab_cmd[i].args)
    {
        free(data->tab_cmd[i].args);
        i++;
    }
    free(data->tab_cmd);
}

int ft_check_cat(t_data *data)
{
    int i;
    char *str;

    i = data->nbr_cmd;
    if (!data->tab_cmd[0].args[0] || data->nbr_cmd == 1)
        return (0);
    while (i != 0)
    {
        if (ft_strncmp(data->tab_cmd[i - 1].args[0], "cat\0", 4) == 0)
        {
            str = readline("");
            free(str);
        }
        i--;
    }
    return (0);
}

int ft_init_envp(t_data *data, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    data->envp = ft_calloc(i + 1, sizeof(char*));
    i = 0;
    while (envp[i])
    {
        data->envp[i] = ft_strdup(envp[i]);
        i++;
    }
    data->envp[i] = NULL;
    return (0);
}

int main(int argc, char **argv, char **envp) 
{
    t_data data;
    struct termios sig;
    
    ft_init_envp(&data, envp);
    init_signals(&sig);
    if (argc == 1)
    {
        while (1)
        {
            ft_init_struct(&data);
            data.str_rl = readline("$ ");//free
            if (!data.str_rl)
                break ;
            add_history(data.str_rl);
            ft_create_str_chunck(&data);
            data.tab_chunck = ft_split(data.str_chunk, '\n');//free
            ft_dollar(data.tab_chunck);
            ft_init_cmd(&data);
            ft_exit_prog(&data);
            ft_exec_cmds(&data);
            ft_check_cat(&data);
            for(int i_cmd = 0; data.tab_cmd[i_cmd].args; i_cmd++)
                for(int i_arg = 0; data.tab_cmd[i_cmd].args[i_arg]; i_arg++)
                    printf("str_tab_args[%d][%d] = %s\n",i_cmd, i_arg, data.tab_cmd[i_cmd].args[i_arg]);
            ft_free(&data);
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &sig);
    }
    else
        printf("Error argument\n");
    free(data.str_chunk);
    (void)argv;
    return 0; 
}

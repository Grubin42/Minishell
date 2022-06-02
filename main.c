/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschreye <jschreye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:05:12 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/02 16:33:32 by jschreye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_print_tab(char **tab)
{
    int i = 0;

    while (tab[i])
    {
        printf("tab = %s\n", tab[i]);
        i++;
    }
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

    i = 0;
    data->nbr_cat = 0;
    if (!data->tab_cmd[0].args[0])
        return (0);
    if (ft_strncmp(data->tab_cmd[0].args[0], "cat\0", 4) == 0)
    {
        data->nbr_cat = 1;
        while (ft_strncmp(data->tab_cmd[i].args[0], "cat\0", 4) == 0
                && ft_strncmp(data->tab_cmd[i + 1].args[0], "cat\0", 4) == 0)
        {
            data->nbr_cat++;
            i++;
        }
        while (data->nbr_cat != 0)
        {
            str = readline("");
            free(str);
            data->nbr_cat--;
        }
    }
    return (0);
}

int main(int argc, char **argv, char **envp) 
{
    t_data data;

    data.envp = envp;
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
            ft_exec_cmds(&data);
            ft_check_cat(&data);
            //for(int i_cmd = 0; data.tab_cmd[i_cmd].args; i_cmd++)
              //  for(int i_arg = 0; data.tab_cmd[i_cmd].args[i_arg]; i_arg++)
                //    printf("str_tab_args[%d][%d] = %s\nPATH = %s\n",i_cmd, i_arg, data.tab_cmd[i_cmd].args[i_arg], data.tab_cmd[i_cmd].path);
            ft_free(&data);
        }
    }
    else
        printf("Error argument\n");
    (void)argv;
    return 0; 
}

#include "minishell.h"

int ft_init_struct(t_data *data)
{
    data->str_getenv = malloc(2048 * sizeof(char));
    data->str_rl = malloc(2048 * sizeof(char));
    data->str_path = malloc(2048 * sizeof(char));
    data->str_getenv = getenv("PATH");
    data->tab_getenv = ft_split(data->str_getenv, ':');
    return (0);
}

int ft_exec_cmd(t_data *data, char **envp)
{
    pid_t   pid;
    int     status;

    status = 0;
    pid = fork();
    if (pid == -1)
		perror("fork");
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        kill(pid, SIGTERM);
    }
    else
    {
        if(execve(data->str_path, &data->tab_rl[0], envp) == - 1)
            perror("shell");
        exit(EXIT_FAILURE);
    }
    return (0);
}

int ft_access_path(t_data *data)
{
    int i;
    int len;
    char *final_path;

    len = ft_strlen(data->tab_rl[0]);
    final_path = malloc(len * sizeof(char) + 1);
    final_path = ft_strdup("");
    final_path = ft_strjoin("/", data->tab_rl[0]);
    i = 0;
    while (data->tab_getenv[i])
    {
        data->str_path = ft_strjoin(data->tab_getenv[i], final_path);
        if (!access(data->str_path, X_OK))
            return (1);
        i++;
    }
    free(final_path);
    return (0);
}

int ft_count_quote(t_data *data)
{
    int i;

    i = 0;
    data->count_sq = 0;
    data->count_dq = 0;
    while (data->str_rl[i])
    {
        if (data->str_rl[i] == 39)
            data->count_sq++;
        if (data->str_rl[i] == 34)
            data->count_dq++;
        i++;
    }
    return (0);
}

int ft_del_consec_quote(t_data *data)
{
    int i;

    i = 0;
    while (data->str_rl[i])
    {
        if ((data->str_rl[i] == 39 && data->str_rl[i + 1] == 39)
            || (data->str_rl[i] == 34 && data->str_rl[i + 1] == 34))
        {
            ft_memmove(&data->str_rl[i], &data->str_rl[i + 2], ft_strlen(data->str_rl) - i);
            i = 0;
        }
        else
            i++;
    }
    return(0);
}

int ft_check_first_quote(t_data *data)
{
    int i;

    i = 0;
    while (data->str_rl[i])
    {
        if (data->str_rl[i] == 39)
            return(1);
        else if (data->str_rl[i] == 34)
            return(2);
        i++;
    }
    return (0);
}

int ft_prompt_quote(t_data *data)
{
    char *new_str;

    new_str = malloc(2048 * sizeof(char));
    ft_count_quote(data);
    if (data->count_sq  % 2 == 1 && ft_check_first_quote(data) == 1)
        new_str = readline("quote> ");//ajouter \n
    else if (data->count_dq % 2 == 1 && ft_check_first_quote(data) == 2)
        new_str = readline("dquote> ");
    if (new_str[0] == 39 && new_str[1] != 39)
        data->str_rl = ft_strjoin(data->str_rl, new_str);
    else if (new_str[0] == 34 && new_str[1] != 34)
        data->str_rl = ft_strjoin(data->str_rl, new_str);
    else
    {
        ft_prompt_quote(data);
    }
    free(new_str);
    return (0);
}

int ft_check_quote(t_data *data)
{
    int i;

    i = 0;
    ft_count_quote(data);
    if (data->count_sq  % 2 == 1 || data->count_dq  % 2 == 1)
        ft_prompt_quote(data);
    ft_del_consec_quote(data);
    printf("str_rl = %s\n", data->str_rl);
    return (0);
}

int main(int argc, char **argv, char **envp) 
{
    t_data data;
    //int i = 0;

    ft_init_struct(&data);
    while (1)
    {
        data.str_rl = readline("$ ");
        add_history(data.str_rl);
        ft_check_quote(&data);
        data.tab_rl = ft_split(data.str_rl, ' ');
        if(!data.tab_rl || !data.tab_rl[0])
            continue; 
        ft_access_path(&data);
        ft_exec_cmd(&data, envp);   
    }
  	(void)argc;//tester que argc soit = 1
	(void)argv;
    (void)envp;
    return 0; 
}
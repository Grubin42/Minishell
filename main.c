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

int ft_count_quote(char *str)
{
    int i;
    int sq;
    int dq;

    i = 0;
    sq = 0;
    dq = 0;
    while (str[i])
    {
        if (str[i] == 39 && ft_check_first_quote(str) == 1)
            sq++;
        else if (str[i] == 34 && ft_check_first_quote(str) == 2)
            dq++;
        i++;
    }
    if (sq % 2 == 1 || dq % 2 == 1)
        return (1);
    return (0);
}

int ft_check_first_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 39)
            return(1);
        else if (str[i] == 34)
            return(2);
        i++;
    }
    return (0);
}

char *ft_del_quote(char *str)// pas fini
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = ft_strlen(str);
    while (str[i])
    {
        if (str[i] == (char)39 || str[i] == (char)34)
            ft_memmove(&str[i], &str[i + 1], len - i);
        i++;
    }
    return(str);
}

char *ft_check_new_quote(char *new_str)
{
    char sq;
    char dq;
    int i;
    int len;

    sq = (char)39;
    dq = (char)34;
    i = 0;
    len = ft_strlen(new_str);
    while (new_str[i])
    {
        if (new_str[i] == sq)
            i++;
        else
            ft_memmove(&new_str[i], &new_str[i + 1], len - i);
    }
    printf("new_str = %s\n", new_str);
    return(new_str);
}

char *ft_check_new_dquote(char *new_str)
{
    char sq;
    char dq;
    int i;
    int len;

    sq = (char)39;
    dq = (char)34;
    i = 0;
    len = ft_strlen(new_str);
    while (new_str[i])
    {
        if (new_str[i] == dq)
            i++;
        else
            ft_memmove(&new_str[i], &new_str[i + 1], len - i); 
    }
    return(new_str);
}

char *ft_prompt_quote(char *str)
{
    char *new_str;

    new_str = malloc(2048 * sizeof(char));
    if (ft_check_first_quote(str) == 1)
    {
        new_str = readline("quote> ");
        new_str = ft_check_new_quote(new_str);
        if (new_str[0] == (char)39)
            str = ft_strjoin(str, &new_str[0]);
        else
            str = ft_prompt_quote(new_str);
    }
    else if (ft_check_first_quote(str) == 2)
    {
        new_str = readline("dquote> ");
        new_str = ft_check_new_dquote(new_str);
        if (new_str[0] == (char)34)
            str = ft_strjoin(str, &new_str[0]);     
        else
            str = ft_prompt_quote(new_str);
    }
    if (ft_count_quote(str) == 1)
        str = ft_prompt_quote(str);
    return (str);
}

int ft_check_quote(t_data *data)
{
    int i;

    i = 0;
    ft_chunck_quote();//A FAIRE
    if (ft_count_quote(data->str_rl) == 1)
        data->str_rl = ft_prompt_quote(data->str_rl);
    //data->str_rl = ft_del_quote(data->str_rl);
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
        //data.tab_rl = ft_split(data.str_rl, ' ');
        //if(!data.tab_rl || !data.tab_rl[0])
            //continue; 
        //ft_access_path(&data);
        //ft_exec_cmd(&data, envp);   
    }
  	(void)argc;//tester que argc soit = 1
	(void)argv;
    (void)envp;
    return 0; 
}
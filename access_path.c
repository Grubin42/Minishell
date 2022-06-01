#include "minishell.h"

int ft_exec_cmd(t_data *data, int i_cmd)
{
    pid_t   pid;
    int     status;

    status = 0;
    pid = fork();
    if (pid == -1)
		perror("fork");
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
    {
        if(execve(data->str_path, data->tab_cmd[i_cmd].args, data->envp) == - 1)
            perror("shell");
        exit(EXIT_FAILURE);
    }
    if (data->str_path)
        free(data->str_path);
    return (0);
}

int ft_access_path(t_data *data, int i_cmd, int  i_arg)
{
    int i;
    char *final_path;

    final_path = ft_join("/", *data->tab_cmd[i_cmd].args);
    i = 0;
    while (data->tab_getenv[i])
    {
        data->str_path = ft_join(data->tab_getenv[i], final_path);
        if (!access(data->str_path, X_OK))
            break ;
        i++;
        free(data->str_path);
        data->str_path = NULL;
    }
    if (data->str_path && i_arg < 1)
    {
        data->tab_cmd[i_cmd].path = ft_calloc(ft_strlen(data->str_path), sizeof(char));// free
        data->tab_cmd[i_cmd].path = ft_strcpy(data->tab_cmd[i_cmd].path, data->str_path);
    }
    free(final_path);
    ft_exec_cmd(data, i_cmd);
    return (0);
}
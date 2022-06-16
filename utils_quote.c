#include "minishell.h"

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
        if (str[i] == 39)
            sq++;
        else if (str[i] == 34)
            dq++;
        i++;
    }
    if (ft_check_first_quote(str) == 1)
        return (sq);
    else if (ft_check_first_quote(str) == 2)
        return (dq);
    return (0);
}

int ft_remove_quote(char *str, int i, char quote)
{
    int len;

    len = ft_strlen(str);
    ft_memmove(&str[i], &str[i + 1], len - i);
    len = ft_strlen(str);
    while (str[i])
    {
        if (str[i] == quote)
        {
            ft_memmove(&str[i], &str[i + 1], len - i);
            return (i);
        }
        i++;
    }
    return (i);
}

int ft_delete_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            i = ft_remove_quote(str, i, '\'');
        else if (str[i] == '"')
            i = ft_remove_quote(str, i, '"');
        else
            i++;
    }
    return (i);
}

int ft_del_quote(t_data *data)
{
    int i_cmd;
    int i_arg;

    i_cmd = 0;
    while (i_cmd < data->nbr_cmd)
    {
        i_arg = 0;
        while (i_arg < ft_count_args(data, i_cmd))
        {
            if (ft_count_quote(data->tab_cmd[i_cmd].args[i_arg]) % 2 != 0)
            {
                printf("Error quote.\n");
                return (1);
            }
            else
                ft_delete_quote(data->tab_cmd[i_cmd].args[i_arg]);
            i_arg++;
        }
        i_cmd++;
    }
    return (0);
}











/*
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
*/
/*
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
*/
/*
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
*/
/*
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
*/
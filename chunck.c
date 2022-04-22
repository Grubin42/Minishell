#include "minishell.h"

int ft_if_sq(t_data *data)
{
    int i;
    int count;
    char *back_n;
    
    count = 0;
    back_n = "\n";
    i = 0; 
    while (data->str_rl[i])
    {
        if (ft_count_quote(data->str_rl) == 1)
        {
            data->str_chunk[data->i_chunk] = data->str_rl[i];
            data->i_chunk++;
            i++;  
        }
        else
        {
            count++;
            data->str_chunk[data->i_chunk] = data->str_rl[i];
            data->i_chunk++;
            i++;
            if (count > 2)
                break;
            while (data->str_rl[i] != (char)39 && data->str_rl[i])
            {
                data->str_chunk[data->i_chunk] = data->str_rl[i];
                data->i_chunk++;
                i++;
            }
            count++;
        }   
    }
    ft_memmove(data->str_rl, data->str_rl + i , ft_strlen(data->str_rl));
    data->str_chunk = ft_strjoin(data->str_chunk, back_n);
    data->i_chunk++;
    printf("str_chunk = %s\n", data->str_chunk);
    return (0);
}

int ft_create_chunck(t_data *data)
{   
    int i = 0;

    data->i_chunk = 0;
    while (data->str_rl[i])
    {
        printf("str_rl = %s\n", data->str_rl);
        if (data->str_rl[0] == (char)39)
        {
            ft_if_sq(data);
            i = 0;
                //si count_quote = 1  enregistre tout
                //sinon enregistre jusqu a la suivante
                //il faut mememove
        }
            /*else if (data->str_rl[i] == (char)34)
            {
                i = 0;
                //faire fonction
                //si count_quote = 1  enregistre tout
                //sinon enregistre jusqu a la suivante
                //il faut mememove
            }
            else if (data->str_rl[i])
            {
                i = 0;
                //faire fonction
                //il faut mememove
            }*/
        else
            i++;
    }
    free(data->str_chunk);
    return (0);
}

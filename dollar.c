/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:39:08 by grubin            #+#    #+#             */
/*   Updated: 2022/05/17 17:13:02 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_include_env(char **str, char *result, int size_env)
{
    int i;
    int i_tok;
    int i_res;
    char *token_tmp;
    
    i = 0;
    i_res = 0;
    i_tok = 0;
    token_tmp = ft_calloc((ft_strlen(*str) + ft_strlen(result)), sizeof(char));// free
    //printf("token AVANT = %s\n", token_tmp);
   // printf("str AVANT = %s\nstr size = %zu\n",*str, ft_strlen(*str));
    while ((*str)[i])
    {
        printf("result = %s\n", result);
        if ((*str)[i] == '$')
        {
            while (result[i_res])
            {
                token_tmp[i_tok] = result[i_res];
                i_tok++;
                i_res++;
            }
            i = i + (size_env + 1);
            i_res = i;
        }
        token_tmp[i_tok] = (*str)[i];
        i++;
        i_tok++;
    }
    *str = token_tmp;// str pas free
    printf("str APRES = %s\n", *str);
    printf("i = %d\n", i);
   // printf("i_res = %d\n", i_res);
    return (i_res);// return une valeur i;
}

int ft_check_env(char **str, int i)
{
    int     i_env;
    char    *env_tmp;
    char    *result;
    //printf("i AVANT = %d\n", i);
    i_env = 0;
    env_tmp = ft_calloc(ft_strlen(*str), sizeof(char));//free
    i++;
    while ((*str)[i])
    {
        if ((*str)[i] == '"' || (*str)[i] == ' ' || (*str)[i] == '$')
            break ;
        env_tmp[i_env] = (*str)[i];
        i++;
        i_env++;
    }
    //printf("i PENDANT = %d\n", i);
    result = getenv(env_tmp);//pas free
    i = ft_include_env(str, result, ft_strlen(env_tmp));
    //printf("i APRES = %d\n", i);
    free(env_tmp);
    return (i);
}

int ft_check_str_with_dollar(char **str)
{
    int i;
    
    i = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == '"' && (*str)[i + 1] != '\0')
        {    
            i++;
            while ((*str)[i] != '"')
            {
                if ((*str)[i] == '$' && (*str)[i + 1] != ' ')
                {
                i = ft_check_env(str, i);
  
                }
                else
                    i++;
            } 
        }
        else if ((*str)[i] == '$')
        {
            
        }
        else
        {
            i++;
        }
    }
    return (0);
}

int ft_check_dollar(char **str)
{
    int i;

    i = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == '$')
        {
            ft_check_str_with_dollar(str);
            break ;
        }
        i++;
    }
    return (0);
}

int ft_dollar(t_cmd *tab)
{
    int i_cmd;
    int i_arg;
    
    i_cmd = 0;
    while (tab[i_cmd].args)
    {
        i_arg = 0;
        while (tab[i_cmd].args[i_arg])
        {
            ft_check_dollar(&tab[i_cmd].args[i_arg]);
            i_arg++;
        }
        i_cmd++;
    }
    return (0);
}
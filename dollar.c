/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:39:08 by grubin            #+#    #+#             */
/*   Updated: 2022/06/15 13:25:59 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_get_env(t_env *env)
{
    int i;
    int i_env;

    i = 0;
    i_env = 0;
    while (env->str_tmp[i])
    {
        if (env->str_tmp[i] == '$')
        {
            i++;
            while (ft_isalpha(env->str_tmp[i]) == 1)
            {
                env->env_tmp[i_env] = env->str_tmp[i];
                i++;
                i_env++;
            }
            break;
        }
        i++;
    }
    env->size_env = ft_strlen(env->env_tmp);
    env->result = getenv(env->env_tmp);
    free(env->env_tmp);
    return (env->result);
}

int ft_change_env(t_env *env, int i)
{
    ft_init_env(env);
    env->result = ft_get_env(env);
    if (env->result == NULL)
        env->result = ft_strdup("");
    i = 0;
    while ((size_t)i < ft_strlen(env->str_tmp))
    {
        if (env->str_tmp[i] == '$' && env->count < 1)
        {
            env->count++;
            while (env->result[env->i_res])
            {
                env->tmp[env->i_tmp] = env->result[env->i_res];
                env->i_tmp++;
                env->i_res++;
            }
            i = i + (env->size_env + 1);
        }
        env->tmp[env->i_tmp] = env->str_tmp[i];
        env->i_tmp++;
        i++;
    }
    env->str_tmp = ft_realloc(env->str_tmp, 2048);
    ft_strlcpy(env->str_tmp, env->tmp, ft_strlen(env->tmp) + 1);
    return (i);
}

int ft_no_change(t_env *env, int i)
{
    env->tmp = ft_calloc(2048, sizeof(char));
    while (env->str_tmp[i])
    {
        env->tmp[i] = env->str_tmp[i];
        i++;
    }
    return (i);
}

int ft_include_env(t_env *env)
{
    int i;

    i = 0;
    while (env->str_tmp[i])
    {
        i = ft_check_quote(env, i);
        if (env->str_tmp[i] == '"' && env->str_tmp[i + 1] != '\0')
        {
            i++;
            i = ft_check_dollar(env, i);
        }
        else if (env->str_tmp[i] == '$' && env->str_tmp[i + 1] == '\'')
            ft_memmove(&env->str_tmp[i], &env->str_tmp[i + 1], ft_strlen(env->str_tmp));
        else if ((env->str_tmp[i] == '$' && env->str_tmp[i + 1] == '"')
            || (env->str_tmp[i] == '$' && env->str_tmp[i + 1] == '\0'))
            i = ft_no_change(env, i);
        else if (env->str_tmp[i] == '$' && env->str_tmp[i + 1] == '?')
            i = ft_change_env(env, i);
        else
            i++;
    }
    return (0);
}

int ft_dollar(char **tab)
{
    t_env env;
    int i;
    
    env.env_tmp = NULL;
    env.result = NULL;
    env.str_tmp = NULL;
    env.tmp = NULL;
    i = 0;
    while (tab[i])
    {
        if (ft_strchr(tab[i], '$'))
        {
            env.str_tmp = ft_strdup(tab[i]);//free
            ft_include_env(&env);
            tab[i] = ft_realloc(tab[i], 2048);
            ft_strlcpy(tab[i], env.str_tmp, ft_strlen(env.str_tmp) + 1);
            free(env.str_tmp);
            i++;
        }
        else
            i++;
    }
    free(env.tmp);
    return (0);
}
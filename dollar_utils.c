/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschreye <jschreye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:39:43 by jschreye          #+#    #+#             */
/*   Updated: 2022/06/02 13:41:17 by jschreye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_quote(t_env *env, int i)
{
    if (env->str_tmp[i] == '\'')
    {
        i++;
        while (env->str_tmp[i] != '\'')
            i++;
    }
    return (i);
}

int ft_check_dollar(t_env *env, int i)
{
    while (env->str_tmp[i])
    {
        if (env->str_tmp[i] == '$' && env->str_tmp[i + 1] != ' ')
            i = ft_change_env(env, i);
        else
            i++;
    } 
    return (i);
}
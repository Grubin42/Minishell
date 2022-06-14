/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grubin <grubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:59:37 by grubin            #+#    #+#             */
/*   Updated: 2022/06/14 10:49:50 by grubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t size)
{
    void* new_data;

    new_data = NULL;
    if(size)
    {
        if(!ptr)
            return (ft_calloc(size, sizeof(char))); //marche uniquement pour des chars revenir sur un malloc size si besoin
        new_data = ft_calloc(size, sizeof(char)); //marche uniquement pour des chars revenir sur un malloc size si besoin
        free(ptr);
    }
    return (new_data);
}
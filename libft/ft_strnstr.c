/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:24:39 by lylaurol          #+#    #+#             */
/*   Updated: 2024/05/29 17:25:44 by lylaurol         ###   ########.fr
       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char* big, const char* little, size_t len)
{
    size_t i;
    size_t j;

    if (!*little)
        return ((char*)big);
    if (len == 0)
        return (NULL);

    i = 0;
    while (big[i] && i < len)
    {
        if (big[i] == little[0])
        {
            j = 0;
            while (little[j] && big[i + j] && (i + j) < len && big[i + j] == little[j])
                j++;
            if (!little[j])
                return ((char*)&big[i]);
        }
        i++;
    }
    return (NULL);
}
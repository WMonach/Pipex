/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:23:53 by wmonacho          #+#    #+#             */
/*   Updated: 2022/01/25 11:24:25 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*dest;

	dest = (void *)malloc(sizeof(t_list));
	if (!dest)
		return (NULL);
	dest->content = content;
	dest->next = NULL;
	return (dest);
}

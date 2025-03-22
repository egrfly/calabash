/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_str_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:46:26 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 15:58:41 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"

t_list	*duplicate_str_list(
			t_list *list)
{
	t_list_node	*list_node;
	t_list		*new_list;

	if (!list)
		return (NULL);
	new_list = ft_list_init();
	list_node = list->first;
	while (list_node)
	{
		if (!ft_list_append(new_list, ft_strdup(list_node->value)))
		{
			ft_list_destroy(new_list, free);
			new_list = NULL;
			break ;
		}
		list_node = list_node->next;
	}
	return (new_list);
}

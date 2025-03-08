/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_starting_with.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:47:45 by aistok            #+#    #+#             */
/*   Updated: 2025/03/08 21:10:58 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_string.h"

#define FIRST_CHAR 0

char	*get_line_starting_with(
			t_list *list, char *starting_with, char *delim_char)
{
	t_list_node	*list_node;

	if (!list || !starting_with)
		return (NULL);
	list_node = list->first;
	while (list_node)
	{
		if (ft_strstarts(list_node->value, starting_with))
		{
			if (!delim_char)
				return (list_node->value);
			if (!ft_strchr(list_node->value, delim_char[FIRST_CHAR]))
				return (NULL);
			return (&ft_strchr(list_node->value, delim_char[FIRST_CHAR])[1]);
		}
		list_node = list_node->next;
	}
	return (NULL);
}

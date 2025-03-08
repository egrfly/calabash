/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values_from_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:53:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 09:19:22 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_stdlib.h"

char	**get_values_from_list(
			t_list *list)
{
	char		**values;
	t_list_node	*current_node;
	size_t		i;

	values = ft_calloc(list->size + 1, sizeof(char *));
	if (!values)
		return (NULL);
	current_node = list->first;
	i = 0;
	while (i < list->size)
	{
		values[i] = current_node->value;
		current_node = current_node->next;
		i++;
	}
	return (values);
}

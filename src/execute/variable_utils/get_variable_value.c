/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:20:09 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 20:26:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"

char	*get_variable_value(
			t_list *variables,
			char *variable_name)
{
	size_t		variable_name_length;
	t_list_node	*current_variable_node;
	char		*current_variable;

	variable_name_length = ft_strlen(variable_name);
	current_variable_node = variables->first;
	while (current_variable_node)
	{
		current_variable = current_variable_node->value;
		if (ft_strstarts(current_variable, variable_name))
		{
			if (!current_variable[variable_name_length])
				return (&current_variable[variable_name_length]);
			if (current_variable[variable_name_length] == '=')
				return (&current_variable[variable_name_length + 1]);
		}
		current_variable_node = current_variable_node->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:20:09 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 13:28:31 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../parse/word_utils/word_utils.h"
#include "./var_utils.h"

char	*get_var_value(
			char *var_name,
			t_list *vars)
{
	size_t		var_name_length;
	t_list_node	*current_var_node;
	char		*current_var;

	if (!is_identifier(var_name))
		return (NULL);
	var_name_length = ft_strlen(var_name);
	current_var_node = vars->first;
	while (current_var_node)
	{
		current_var = current_var_node->value;
		if (ft_strstarts(current_var, NOT_EXPORTED_PREFIX))
			current_var++;
		if (vars_have_same_name(var_name, current_var))
		{
			if (current_var[var_name_length] == '=')
				return (&current_var[var_name_length + 1]);
			else
				return ("");
		}
		current_var_node = current_var_node->next;
	}
	return (NULL);
}

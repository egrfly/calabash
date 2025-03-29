/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:20:09 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/22 15:01:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../parse/word_utils/word_utils.h"
#include "./var_utils.h"

char	*get_var_value_n(
			char *var_name,
			size_t n,
			t_list *vars)
{
	size_t		var_name_length;
	t_list_node	*current_var_node;
	char		*current_var;

	if (!range_is_identifier(var_name, 0, n))
		return (NULL);
	var_name_length = n;
	current_var_node = vars->first;
	while (current_var_node)
	{
		current_var = current_var_node->value;
		if (ft_strstarts(current_var, NOT_EXPORTED_PREFIX))
			current_var++;
		if (vars_have_same_name_n(var_name, n, current_var))
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

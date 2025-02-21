/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is_of_a_control_structure_type.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 04:47:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:03:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../parse.h"

static const
	t_syntax_tree_node_value_type
	g_control_structure_node_value_types[] = {
	WHILE_COMMAND,
	UNTIL_COMMAND,
	IF_COMMAND,
	FOR_COMMAND,
	SELECT_COMMAND,
	CASE_COMMAND,
};

bool	node_is_of_a_control_structure_type(
			t_syntax_tree_node_value *node_value)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_control_structure_node_value_types)
		/ sizeof(t_syntax_tree_node_value_type))
	{
		if (node_value->type == g_control_structure_node_value_types[i])
			return (true);
		i++;
	}
	return (false);
}

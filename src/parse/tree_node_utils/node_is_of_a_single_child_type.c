/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is_of_a_single_child_type.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:55:28 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:04:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../parse.h"

static const
	t_syntax_tree_node_value_type
	g_single_child_node_value_types[] = {
	GROUP,
	SUBSHELL,
	FUNCTION,
	TIME_COMMAND,
	NEGATION,
	BACKGROUND,
	COPROCESS,
};

bool	node_is_of_a_single_child_type(
			t_syntax_tree_node_value *node_value)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_single_child_node_value_types)
		/ sizeof(t_syntax_tree_node_value_type))
	{
		if (node_value->type == g_single_child_node_value_types[i])
			return (true);
		i++;
	}
	return (false);
}

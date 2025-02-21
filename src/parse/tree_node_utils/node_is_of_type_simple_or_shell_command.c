/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is_of_type_simple_or_shell_command.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:07:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:04:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../parse.h"

static const
	t_syntax_tree_node_value_type
	g_simple_or_shell_command_node_value_types[] = {
	SIMPLE_COMMAND,
	GROUP,
	SUBSHELL,
	WHILE_COMMAND,
	UNTIL_COMMAND,
	IF_COMMAND,
	FOR_COMMAND,
	SELECT_COMMAND,
	CASE_COMMAND,
};

bool	node_is_of_type_simple_or_shell_command(
			t_syntax_tree_node_value *node_value)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_simple_or_shell_command_node_value_types)
		/ sizeof(t_syntax_tree_node_value_type))
	{
		if (node_value->type == g_simple_or_shell_command_node_value_types[i])
			return (true);
		i++;
	}
	return (false);
}

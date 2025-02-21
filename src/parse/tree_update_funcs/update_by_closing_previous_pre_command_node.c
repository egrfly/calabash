/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_by_closing_previous_pre_command_node        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:56:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:35:06 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_update_utils/tree_update_utils.h"

bool	update_by_closing_previous_pre_command_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	t_syntax_tree_node_value_type	new_node_type;

	new_node_type = get_node_type_from_token(current_token_node->value);
	while (syntax_tree->current_node->parent
		&& !node_is_of_type(syntax_tree->current_node->value, new_node_type))
		if (!adjust_current_node_from_child_to_parent(syntax_tree))
			return (false);
	return (true);
}

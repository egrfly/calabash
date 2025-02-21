/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_with_new_mid_or_post_command_node.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:56:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:36:24 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_update_utils/tree_update_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	update_with_new_mid_or_post_command_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	t_syntax_tree_node_value_type	new_node_type;

	new_node_type = get_node_type_from_token(current_token_node->value);
	if (!slot_new_node_up_tree_between_nodes_of_suitable_precedences(
			new_node_type, syntax_tree))
		return (false);
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_current_node_from_primary_child_to_parent))
		return (false);
	syntax_tree->current_node = syntax_tree->current_node->parent;
	return (true);
}

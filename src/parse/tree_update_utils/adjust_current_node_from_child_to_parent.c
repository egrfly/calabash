/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_current_node_from_child_to_parent.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:36:50 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:03:18 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	adjust_current_node_from_child_to_parent(
			t_syntax_tree *syntax_tree)
{
	t_tree_undo_action_func	undo_action_func;

	if (node_is_primary_child_of_parent(syntax_tree->current_node))
		undo_action_func
			= undo_set_current_node_from_primary_child_to_parent;
	else if (node_is_secondary_child_of_parent(syntax_tree->current_node))
		undo_action_func
			= undo_set_current_node_from_secondary_child_to_parent;
	else
		return (false);
	if (!ft_list_append(syntax_tree->undo_actions, undo_action_func))
		return (false);
	syntax_tree->current_node = syntax_tree->current_node->parent;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_by_moving_current_node_up_to_control        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 04:42:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 02:52:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_update_utils/tree_update_utils.h"

bool	update_by_moving_current_node_up_to_control_structure_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	(void)current_token_node;
	while (syntax_tree->current_node->parent
		&& !node_is_of_a_control_structure_type(
			syntax_tree->current_node->value))
		if (!adjust_current_node_from_child_to_parent(syntax_tree))
			return (false);
	return (true);
}

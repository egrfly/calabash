/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_by_moving_current_node_up_to_functio        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:54:32 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 15:40:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_update_utils/tree_update_utils.h"

bool	update_by_moving_current_node_up_to_function_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node,
			t_multiline_options *multiline_options)
{
	(void)current_token_node;
	(void)multiline_options;
	while (syntax_tree->current_node->parent
		&& !node_is_of_type_function(syntax_tree->current_node->value))
		if (!adjust_current_node_from_child_to_parent(syntax_tree))
			return (false);
	return (true);
}

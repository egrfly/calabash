/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_tree_root_and_current_node_to_new_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:39:16 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 01:12:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"
#include "../tree_node_lifecycle/tree_node_lifecycle.h"

void	undo_set_tree_root_and_current_node_to_new_non_null_node(
			t_syntax_tree *syntax_tree)
{
	destroy_syntax_tree_node(syntax_tree->current_node);
	syntax_tree->current_node = NULL;
	syntax_tree->tree->root = NULL;
}

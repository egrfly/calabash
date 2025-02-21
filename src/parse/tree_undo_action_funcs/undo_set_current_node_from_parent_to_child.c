/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_current_node_from_parent_to_child.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:48:58 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:49:43 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	undo_set_current_node_from_parent_to_child(
			t_syntax_tree *syntax_tree)
{
	syntax_tree->current_node = syntax_tree->current_node->parent;
}

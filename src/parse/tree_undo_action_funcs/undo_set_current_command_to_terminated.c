/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_current_command_to_terminated.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:52:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:54:06 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

void	undo_set_current_command_to_terminated(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;

	current_node_value = syntax_tree->current_node->value;
	current_node_value->is_terminated = false;
}

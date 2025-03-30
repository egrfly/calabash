/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_command_to_terminated.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 04:42:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 15:40:59 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	update_command_to_terminated(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node,
			t_multiline_options *multiline_options)
{
	t_syntax_tree_node_value	*current_node_value;

	(void)current_token_node;
	(void)multiline_options;
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_current_command_to_terminated))
		return (false);
	current_node_value = syntax_tree->current_node->value;
	current_node_value->is_terminated = true;
	return (true);
}

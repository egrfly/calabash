/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_time_command_to_use_posix_option.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:34:36 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 21:57:14 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../parse.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	update_time_command_to_use_posix_option(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	t_syntax_tree_node_value	*current_node_value;

	(void)current_token_node;
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_time_posix_option))
		return (false);
	current_node_value = syntax_tree->current_node->value;
	current_node_value->time_posix_option_set = true;
	return (true);
}

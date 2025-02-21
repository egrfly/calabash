/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_command_with_new_argument.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:56:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 07:23:23 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"
#include "../tree_update_utils/tree_update_utils.h"

bool	update_command_with_new_argument(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	t_syntax_tree_node_value	*current_node_value;
	t_token						*current_token;
	char						*new_argument;

	if ((!syntax_tree->current_node
			|| node_is_terminated(syntax_tree->current_node->value)
			|| !node_is_of_type_simple_command(
				syntax_tree->current_node->value))
		&& !adjust_current_node_to_accommodate_new_node(SIMPLE_COMMAND,
			syntax_tree))
		return (false);
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_create_assignment))
		return (false);
	current_node_value = syntax_tree->current_node->value;
	current_token = current_token_node->value;
	new_argument = ft_strdup(current_token->content.word);
	if (!new_argument)
		return (ft_list_pop(syntax_tree->undo_actions), false);
	if (!ft_list_append(current_node_value->arguments, new_argument))
	{
		free(new_argument);
		return (ft_list_pop(syntax_tree->undo_actions), false);
	}
	return (true);
}

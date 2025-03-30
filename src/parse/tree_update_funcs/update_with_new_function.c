/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_with_new_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:30:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 15:41:43 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"
#include "../tree_update_utils/tree_update_utils.h"

bool	update_with_new_function(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node,
			t_multiline_options *multiline_options)
{
	t_syntax_tree_node_value	*current_node_value;
	t_token						*current_token;
	char						*new_function_identifier;

	(void)multiline_options;
	if (!adjust_current_node_to_accommodate_new_node(FUNCTION,
			syntax_tree))
		return (false);
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_function_identifier))
		return (false);
	current_node_value = syntax_tree->current_node->value;
	current_token = current_token_node->value;
	new_function_identifier = ft_strdup(current_token->content.word);
	if (!new_function_identifier)
		return (ft_list_pop(syntax_tree->undo_actions), false);
	current_node_value->function_identifier = new_function_identifier;
	return (true);
}

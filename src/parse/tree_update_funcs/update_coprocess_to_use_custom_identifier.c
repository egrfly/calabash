/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_coprocess_to_use_custom_identifier.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:30:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 15:41:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	update_coprocess_to_use_custom_identifier(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node,
			t_multiline_options *multiline_options)
{
	t_syntax_tree_node_value	*current_node_value;
	t_token						*current_token;
	char						*custom_coprocess_identifier;

	(void)multiline_options;
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_coprocess_custom_identifier))
		return (false);
	current_node_value = syntax_tree->current_node->value;
	current_token = current_token_node->value;
	custom_coprocess_identifier = ft_strdup(current_token->content.word);
	if (!custom_coprocess_identifier)
		return (ft_list_pop(syntax_tree->undo_actions), false);
	current_node_value->coprocess_custom_identifier
		= custom_coprocess_identifier;
	return (true);
}

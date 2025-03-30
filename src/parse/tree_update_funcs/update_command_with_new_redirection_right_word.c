/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_command_with_new_redirection_right_w        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:05:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 15:41:27 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../redirection_utils/redirection_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	update_command_with_new_redirection_right_word(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node,
			t_multiline_options *multiline_options)
{
	t_redirection	*last_redirection;
	t_token			*current_token;

	(void)multiline_options;
	last_redirection = get_or_create_redirection(syntax_tree);
	if (!last_redirection)
		return (false);
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_redirection_right_word))
		return (false);
	current_token = current_token_node->value;
	last_redirection->right_type = REDIRECTION_RIGHT_WORD;
	last_redirection->right_content.word
		= ft_strdup(current_token->content.word);
	if (!last_redirection->right_content.word)
		return (false);
	return (true);
}

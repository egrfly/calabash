/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_command_with_new_redirection_right_n        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:05:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 21:57:24 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_stdlib.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../redirection_utils/redirection_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	update_command_with_new_redirection_right_number(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	t_redirection	*last_redirection;
	t_token			*current_token;

	last_redirection = get_or_create_redirection(syntax_tree);
	if (!last_redirection)
		return (false);
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_redirection_right_number))
		return (false);
	current_token = current_token_node->value;
	last_redirection->right_type = REDIRECTION_RIGHT_NUMBER;
	ft_atoi(current_token->content.word,
		&last_redirection->right_content.number);
	return (true);
}

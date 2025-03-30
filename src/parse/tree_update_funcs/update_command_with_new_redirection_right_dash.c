/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_command_with_new_redirection_right_d        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:05:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 15:41:15 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../redirection_utils/redirection_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"

bool	update_command_with_new_redirection_right_dash(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node,
			t_multiline_options *multiline_options)
{
	t_redirection	*last_redirection;

	(void)current_token_node;
	(void)multiline_options;
	last_redirection = get_or_create_redirection(syntax_tree);
	if (!last_redirection)
		return (false);
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_redirection_right_dash))
		return (false);
	last_redirection->right_type = REDIRECTION_RIGHT_DASH;
	return (true);
}

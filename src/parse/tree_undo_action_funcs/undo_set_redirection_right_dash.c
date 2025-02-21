/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_redirection_right_dash.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:06:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 03:25:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	undo_set_redirection_right_dash(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;
	t_redirection				*last_redirection;

	current_node_value = syntax_tree->current_node->value;
	last_redirection = current_node_value->redirections->last->value;
	last_redirection->right_type = NO_REDIRECTION_RIGHT_CONTENT;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_redirection_left_redirection_word.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:15:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 03:27:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"

void	undo_set_redirection_left_redirection_word(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;
	t_redirection				*last_redirection;

	current_node_value = syntax_tree->current_node->value;
	last_redirection = current_node_value->redirections->last->value;
	free(last_redirection->left_content.redirection_word);
	last_redirection->left_content.redirection_word = NULL;
	last_redirection->left_type = NO_REDIRECTION_LEFT_CONTENT;
}

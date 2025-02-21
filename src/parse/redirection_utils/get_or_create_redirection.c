/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_create_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:29:58 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 22:08:44 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "../parse.h"
#include "../redirection_lifecycle/redirection_lifecycle.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"
#include "../tree_update_utils/tree_update_utils.h"
#include "./redirection_utils.h"

static bool	node_not_suitable_for_adding_redirections_to(
				t_binary_tree_node *node)
{
	return (!node
		|| !node_is_of_type_simple_or_shell_command(node->value)
		|| node_is_terminated(node->value));
}

static t_redirection	*append_new_redirection(
							t_syntax_tree *syntax_tree,
							t_list *redirections)
{
	t_redirection	*new_redirection;

	if (!ft_list_append(syntax_tree->undo_actions, undo_create_redirection))
		return (NULL);
	new_redirection = create_redirection();
	if (!new_redirection)
		return (ft_list_pop(syntax_tree->undo_actions), NULL);
	if (!ft_list_append(redirections, new_redirection))
	{
		destroy_redirection(new_redirection);
		return (ft_list_pop(syntax_tree->undo_actions), NULL);
	}
	return (new_redirection);
}

t_redirection	*get_or_create_redirection(
					t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;

	if (node_not_suitable_for_adding_redirections_to(syntax_tree->current_node))
		adjust_current_node_to_accommodate_new_node(
			SIMPLE_COMMAND,
			syntax_tree);
	current_node_value = syntax_tree->current_node->value;
	if (!current_node_value->redirections->last
		|| redirection_has_all_parts_already(
			current_node_value->redirections->last->value))
		return (append_new_redirection(
				syntax_tree,
				current_node_value->redirections));
	else
		return (current_node_value->redirections->last->value);
}

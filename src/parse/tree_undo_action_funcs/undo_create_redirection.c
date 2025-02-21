/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_create_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:21:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:22:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../parse.h"
#include "../redirection_lifecycle/redirection_lifecycle.h"

void	undo_create_redirection(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;
	t_redirection				*last_redirection;

	current_node_value = syntax_tree->current_node->value;
	last_redirection = ft_list_pop(current_node_value->redirections);
	destroy_redirection(last_redirection);
}

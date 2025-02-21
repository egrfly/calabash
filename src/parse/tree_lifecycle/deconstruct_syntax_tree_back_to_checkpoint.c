/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deconstruct_syntax_tree_back_to_checkpoint.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:57:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:59:59 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../parse.h"

void	deconstruct_syntax_tree_back_to_checkpoint(
			t_syntax_tree *syntax_tree,
			t_list_node *checkpoint)
{
	t_tree_undo_action_func	current_undo_action_func;

	while (syntax_tree->undo_actions->last
		&& syntax_tree->undo_actions->last != checkpoint)
	{
		current_undo_action_func = ft_list_pop(syntax_tree->undo_actions);
		current_undo_action_func(syntax_tree);
	}
}

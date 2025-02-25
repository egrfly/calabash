/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_syntax_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:51:08 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 11:35:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../parse.h"
#include "./tree_lifecycle.h"

void	destroy_syntax_tree(t_syntax_tree *syntax_tree)
{
	if (!syntax_tree)
		return ;
	if (syntax_tree->undo_actions)
	{
		deconstruct_syntax_tree_back_to_checkpoint(syntax_tree, BEGINNING);
		ft_list_destroy(syntax_tree->undo_actions, DELETE_NO_OP);
	}
	free(syntax_tree->tree);
	free(syntax_tree);
}

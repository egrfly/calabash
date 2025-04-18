/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tokens_and_syntax_tree.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:05:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/19 17:49:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../../lex/token_lifecycle/token_lifecycle.h"
#include "../../parse/tree_lifecycle/tree_lifecycle.h"
#include "../execute.h"

void	destroy_tokens_and_syntax_tree(
			t_tokens_and_syntax_tree *tokens_and_syntax_tree)
{
	if (!tokens_and_syntax_tree)
		return ;
	ft_list_destroy(tokens_and_syntax_tree->tokens,
		(t_action_func)destroy_token);
	destroy_syntax_tree(tokens_and_syntax_tree->syntax_tree);
}

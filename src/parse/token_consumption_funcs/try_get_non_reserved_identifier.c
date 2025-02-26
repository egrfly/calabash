/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_non_reserved_identifier.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:01:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:25:44 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../word_utils/word_utils.h"

int	try_get_non_reserved_identifier(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	t_token	*current_token;

	(void)arg;
	(void)syntax_tree;
	(void)multiline_options;
	current_token = (*current_token_node)->value;
	if (current_token->type == TYPE_WORD
		&& is_identifier(current_token->content.word)
		&& !is_reserved(current_token->content.word))
	{
		current_token->has_been_consumed_at_some_point = true;
		*current_token_node = (*current_token_node)->next;
		return (1);
	}
	return (0);
}

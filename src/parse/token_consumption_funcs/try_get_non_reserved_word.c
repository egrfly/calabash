/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_non_reserved_word.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:38:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:31:13 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../word_utils/word_utils.h"

int	try_get_non_reserved_word(
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
	if (current_token->type == WORD
		&& !is_reserved(current_token->content.word))
	{
		current_token->has_been_consumed_at_some_point = true;
		*current_token_node = (*current_token_node)->next;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_assignment_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:43:19 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:04:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../word_utils/word_utils.h"

int	try_get_assignment_word(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	t_token	*current_token;
	size_t	word_len;
	char	*first_equals_sign;

	(void)arg;
	(void)syntax_tree;
	(void)multiline_options;
	current_token = (*current_token_node)->value;
	if (current_token->type == TYPE_WORD)
	{
		word_len = ft_strlen(current_token->content.word);
		first_equals_sign = ft_strchr(current_token->content.word, '=');
		if (word_len >= 2
			&& first_equals_sign
			&& range_is_identifier(current_token->content.word,
				0, first_equals_sign - current_token->content.word))
		{
			current_token->has_been_consumed_at_some_point = true;
			*current_token_node = (*current_token_node)->next;
			return (1);
		}
	}
	return (0);
}

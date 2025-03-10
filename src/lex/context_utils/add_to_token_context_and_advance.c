/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_token_context_and_advance.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:11:49 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 08:44:36 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../lex.h"
#include "../content_utils/content_utils.h"
#include "../input_utils/input_utils.h"
#include "./context_utils.h"

static void	advance_line_before_attempting_to_add_to_context(
				t_input_tracker *input_tracker,
				t_token *token,
				bool *out_of_memory)
{
	if (token->type == TYPE_WORD && input_tracker->quote_mode != UNQUOTED)
	{
		extend_word_token_content(input_tracker, token,
			in_escaped_section(input_tracker), out_of_memory);
		if (!in_escaped_section(input_tracker))
			add_newline_to_word_token_content(token, out_of_memory);
	}
	input_tracker->current_input_line
		= get_next_char_pointer(input_tracker);
	input_tracker->line_index++;
	input_tracker->index_in_line = 0;
}

void	add_to_token_context_and_advance(
			t_input_tracker *input_tracker,
			t_token *token,
			bool *out_of_memory)
{
	if (get_current_char(input_tracker) == '\n')
	{
		advance_line_before_attempting_to_add_to_context(input_tracker,
			token, out_of_memory);
		return ;
	}
	if (!token->context_was_truncated
		&& token->length_in_context < MAX_TOKEN_LENGTH_IN_CONTEXT)
	{
		if (token->start_line_index == input_tracker->line_index)
		{
			ft_strncat(token->surrounding_context,
				get_current_char_pointer(input_tracker),
				1);
			token->length_in_context++;
		}
	}
	else
		token->context_was_truncated = true;
	input_tracker->index_in_line++;
}

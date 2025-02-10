/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_last_token_if_exists.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:53:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 17:22:44 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../lex.h"
#include "../content_utils/content_utils.h"
#include "../context_utils/context_utils.h"

void	delimit_last_token_if_exists(
			t_input_tracker *input_tracker,
			t_token *token,
			bool *has_error)
{
	if (token && !token->is_delimited)
	{
		add_token_trailing_context(
			token,
			input_tracker->input,
			input_tracker->index_in_line);
		if (token->type == WORD)
			extend_word_token_content(input_tracker, token, has_error);
		if (token->type == OPERATOR)
			token->content.operator
				= get_operator_token_content(
					input_tracker->input,
					token->start_index_in_start_line,
					input_tracker->index_in_line
					- token->start_index_in_start_line);
		token->is_delimited = true;
	}
}

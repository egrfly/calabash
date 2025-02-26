/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:44:21 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 22:23:27 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../lex.h"
#include "../content_utils/content_utils.h"
#include "../context_utils/context_utils.h"
#include "../token_utils/token_utils.h"

static bool	is_not_valid_operator_continuation(
			t_input_tracker *input_tracker,
			t_token *last_token)
{
	return (last_token->type == TYPE_OPERATOR
		&& !some_operator_starts_with_chars(input_tracker->input,
			last_token->start_index_in_start_line,
			input_tracker->index_in_line
			- last_token->start_index_in_start_line
			+ 1));
}

bool	delimit_operator(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	t_token	*last_token;

	(void)multiline_options;
	last_token = get_last_token(tokens_with_status->tokens);
	if (last_token && !last_token->is_delimited
		&& is_not_valid_operator_continuation(input_tracker, last_token))
	{
		add_token_trailing_context(last_token,
			input_tracker->input,
			input_tracker->index_in_line);
		last_token->content.operator
			= get_operator_token_content(
				input_tracker->input,
				last_token->start_index_in_start_line,
				input_tracker->index_in_line
				- last_token->start_index_in_start_line);
		last_token->is_delimited = true;
		last_token->end_line_index = input_tracker->line_index;
		return (true);
	}
	return (false);
}

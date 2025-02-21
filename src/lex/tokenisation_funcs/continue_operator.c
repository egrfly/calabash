/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:44:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 23:48:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../lex.h"
#include "../content_utils/content_utils.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_operator_continuation(
			t_input_tracker *input_tracker,
			t_token *last_token)
{
	return (last_token->type == OPERATOR
		&& input_tracker->quote_mode == UNQUOTED
		&& some_operator_starts_with_chars(input_tracker->input,
			last_token->start_index_in_start_line,
			input_tracker->index_in_line
			- last_token->start_index_in_start_line
			+ 1));
}

bool	continue_operator(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	t_token	*last_token;

	(void)multiline_options;
	(void)has_error;
	last_token = get_last_token(tokens);
	return (continue_token(
			input_tracker,
			last_token,
			is_valid_operator_continuation));
}

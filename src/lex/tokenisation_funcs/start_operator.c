/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:26:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:31:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../interface/interface.h"
#include "../lex.h"
#include "../content_utils/content_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_operator_start_opportunity(
				t_input_tracker *input_tracker)
{
	return (input_tracker->quote_mode == UNQUOTED
		&& some_operator_starts_with_chars(input_tracker->current_input_line,
			input_tracker->index_in_line,
			1));
}

bool	start_operator(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	(void)multiline_options;
	if (is_valid_operator_start_opportunity(input_tracker))
		return (start_token(input_tracker,
				tokens_with_status,
				create_operator_token));
	return (false);
}

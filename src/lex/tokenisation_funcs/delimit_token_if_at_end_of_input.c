/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_token_if_at_end_of_input.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:52:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:31:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../interface/interface.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_end_of_input_instance(
				t_input_tracker *input_tracker)
{
	return (input_tracker->is_out_of_lines
		|| (input_tracker->quote_mode == UNQUOTED
			&& (!input_tracker->current_input_line
				|| !get_current_char(input_tracker))));
}

bool	delimit_token_if_at_end_of_input(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	(void)multiline_options;
	if (is_valid_end_of_input_instance(input_tracker))
		return (start_token(input_tracker,
				tokens_with_status,
				create_end_of_input_token));
	return (false);
}

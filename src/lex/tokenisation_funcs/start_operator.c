/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:26:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:55:14 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../content_utils/content_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_operator_start_opportunity(
				t_input_tracker *input_tracker)
{
	return (input_tracker->quote_mode == UNQUOTED
		&& some_operator_starts_with_chars(input_tracker->input,
			input_tracker->index_in_line,
			1));
}

bool	start_operator(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	(void)multiline_options;
	if (is_valid_operator_start_opportunity(input_tracker))
		return (start_token(input_tracker,
				tokens,
				create_operator_token,
				has_error));
	return (false);
}

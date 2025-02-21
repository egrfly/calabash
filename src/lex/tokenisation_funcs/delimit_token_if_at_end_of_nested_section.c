/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_token_if_at_end_of_nested_section.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:52:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 21:54:04 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static const
	char
	*g_nesting_mode_closing_symbols[] = {
[DOLLAR_PARENTHESIS_PARENTHESIS] = "))",
[DOLLAR_PARENTHESIS] = ")",
[DOLLAR_BRACE] = "}",
[LESS_PARENTHESIS] = ")",
[GREATER_PARENTHESIS] = ")",
[PARENTHESIS_PARENTHESIS] = "))",
[PARENTHESIS] = ")",
[BACKTICK] = "`",
};

static bool	is_valid_end_of_nested_section_instance(
				t_input_tracker *input_tracker)
{
	return (input_tracker->quote_mode == UNQUOTED
		&& input_tracker->nesting_mode != NOT_NESTED
		&& ft_strstarts(get_current_char_pointer(input_tracker),
			g_nesting_mode_closing_symbols[input_tracker->nesting_mode]));
}

bool	delimit_token_if_at_end_of_nested_section(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	(void)multiline_options;
	if (is_valid_end_of_nested_section_instance(input_tracker))
		return (start_token(input_tracker,
				tokens,
				create_end_of_input_token,
				has_error));
	return (false);
}

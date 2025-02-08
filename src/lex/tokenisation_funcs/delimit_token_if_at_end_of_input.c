/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_token_if_at_end_of_input.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:52:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:58:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_end_of_input_instance(
				t_input_tracker *input_tracker)
{
	return (input_tracker->is_out_of_lines
		|| (input_tracker->quote_mode == UNQUOTED
			&& !get_current_char(input_tracker)));
}

bool	delimit_token_if_at_end_of_input(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	(void)multiline_options;
	if (is_valid_end_of_input_instance(input_tracker))
		return (start_token(input_tracker,
				tokens,
				create_end_of_input_token,
				has_error));
	return (false);
}

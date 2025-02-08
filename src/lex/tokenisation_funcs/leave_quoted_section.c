/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_quoted_section.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:18:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"
#include "../input_utils/input_utils.h"
#include "../token_utils/token_utils.h"

bool	leave_quoted_section(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	t_token	*last_token;

	(void)multiline_options;
	(void)has_error;
	last_token = get_last_token(tokens);
	if (input_tracker->quote_mode == ESCAPED
		|| (input_tracker->quote_mode == SINGLE_QUOTED
			&& get_current_char(input_tracker) == '\'')
		|| (input_tracker->quote_mode == DOUBLE_QUOTED
			&& get_current_char(input_tracker) == '\"'))
	{
		add_to_token_context_if_space_available(input_tracker, last_token);
		input_tracker->index_in_line++;
		input_tracker->quote_mode = UNQUOTED;
		return (true);
	}
	return (false);
}

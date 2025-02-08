/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:12:05 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:26:31 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_ctype.h"
#include "ft_list.h"
#include "../lex.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_whitespace_continuation(
			t_input_tracker *input_tracker,
			t_token *last_token)
{
	return (last_token->type == WHITESPACE
		&& input_tracker->quote_mode == UNQUOTED
		&& ft_isspace(get_current_char(input_tracker)));
}

bool	continue_whitespace(
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
			is_valid_whitespace_continuation));
}

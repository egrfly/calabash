/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:36:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:56:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_ctype.h"
#include "ft_list.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_whitespace_start_opportunity(
				t_input_tracker *input_tracker)
{
	return (input_tracker->quote_mode == UNQUOTED
		&& ft_isspace(get_current_char(input_tracker)));
}

bool	start_whitespace(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	(void)multiline_options;
	if (is_valid_whitespace_start_opportunity(input_tracker))
		return (start_token(input_tracker,
				tokens,
				create_whitespace_token,
				has_error));
	return (false);
}

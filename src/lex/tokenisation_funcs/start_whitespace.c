/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:36:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:09:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_ctype.h"
#include "../../interface/interface.h"
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
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	(void)multiline_options;
	if (is_valid_whitespace_start_opportunity(input_tracker))
		return (start_token(input_tracker,
				tokens_with_status,
				create_whitespace_token));
	return (false);
}

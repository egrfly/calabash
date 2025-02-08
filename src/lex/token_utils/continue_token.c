/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:39:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:28:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../lex.h"
#include "../context_utils/context_utils.h"

bool	continue_token(
			t_input_tracker *input_tracker,
			t_token *last_token,
			bool (*is_valid_token_continuation)(
				t_input_tracker *input_tracker,
				t_token *last_token))
{
	if (last_token
		&& !last_token->is_delimited
		&& is_valid_token_continuation(input_tracker, last_token))
	{
		add_to_token_context_if_space_available(input_tracker, last_token);
		input_tracker->index_in_line++;
		return (true);
	}
	return (false);
}

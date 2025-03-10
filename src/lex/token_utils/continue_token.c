/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:39:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 07:58:29 by emflynn          ###   ########.fr       */
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
				t_token *last_token),
			bool *out_of_memory)
{
	if (last_token
		&& !last_token->is_delimited
		&& is_valid_token_continuation(input_tracker, last_token))
	{
		add_to_token_context_and_advance(input_tracker, last_token,
			out_of_memory);
		return (!*out_of_memory);
	}
	return (false);
}

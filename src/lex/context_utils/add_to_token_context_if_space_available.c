/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_token_context_if_space_available.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:11:49 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:11:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"
#include "./context_utils.h"

void	add_to_token_context_if_space_available(
			t_input_tracker *input_tracker,
			t_token *token)
{
	if (!token->context_is_complete)
	{
		ft_strncat(token->surrounding_context,
			get_current_char_pointer(input_tracker),
			1);
		token->length_in_context++;
		if (token->length_in_context == MAX_TOKEN_LENGTH_IN_CONTEXT)
		{
			add_token_trailing_context(token->surrounding_context,
				input_tracker->input,
				input_tracker->index_in_line,
				token->length_in_context);
			token->context_is_complete = true;
		}
	}
}

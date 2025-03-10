/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_newline_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 05:11:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:23:53 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../lex.h"
#include "./token_lifecycle.h"

static bool	set_newline_specific_properties(t_token *token)
{
	token->type = TYPE_NEWLINE;
	token->length_in_context = BLANK_TOKEN_LENGTH_IN_CONTEXT;
	token->is_delimited = true;
	token->end_line_index = token->start_line_index;
	return (true);
}

t_token	*create_newline_token(
			t_input_tracker *input_tracker,
			bool *out_of_memory)
{
	return (create_token(input_tracker,
			set_newline_specific_properties,
			out_of_memory));
}

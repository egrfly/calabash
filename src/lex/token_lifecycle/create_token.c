/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:20:56 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 06:17:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_stdlib.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"
#include "./token_lifecycle.h"

t_token	*create_token(
			t_input_tracker *input_tracker,
			bool (*set_type_specific_properties)(
				t_token *token),
			bool *has_error)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (!new_token)
	{
		*has_error = true;
		return (NULL);
	}
	new_token->start_line_index = input_tracker->line_index;
	new_token->start_index_in_start_line = input_tracker->index_in_line;
	add_token_leading_context(new_token,
		input_tracker->input, input_tracker->index_in_line);
	new_token->start_index_in_context
		= get_token_start_index_in_context(input_tracker->index_in_line);
	new_token->is_supported = true;
	if (!set_type_specific_properties(new_token))
	{
		*has_error = true;
		destroy_token(new_token);
		return (NULL);
	}
	return (new_token);
}

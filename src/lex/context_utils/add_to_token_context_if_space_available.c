/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_token_context_if_space_available.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:11:49 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 16:55:52 by emflynn          ###   ########.fr       */
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
	if (!token->context_was_truncated
		&& token->length_in_context < MAX_TOKEN_LENGTH_IN_CONTEXT)
	{
		ft_strncat(token->surrounding_context,
			get_current_char_pointer(input_tracker),
			1);
		token->length_in_context++;
	}
	else
		token->context_was_truncated = true;
}

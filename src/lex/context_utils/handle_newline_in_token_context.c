/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline_in_token_context.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:42:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 20:01:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"

static void	remove_last_backslash_from_token_context(
				t_token *token)
{
	token->surrounding_context[ft_strlen(token->surrounding_context) - 1]
		= '\0';
	token->length_in_context--;
}

void	handle_newline_in_token_context(
			t_input_tracker *input_tracker,
			t_token *token)
{
	if (in_escaped_section(input_tracker))
		remove_last_backslash_from_token_context(token);
	else
		token->context_was_truncated = true;
}

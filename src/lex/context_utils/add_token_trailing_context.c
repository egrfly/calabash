/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_trailing_context.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:36:46 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/01 03:52:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "../lex.h"

void	add_token_trailing_context(
			t_token *token,
			const char *input,
			int end_index_in_line)
{
	int	input_line_length;

	input_line_length = ft_strcspn(input, "\n");
	if (token->length_in_context <= MAX_TOKEN_LENGTH_IN_CONTEXT)
		ft_strncat(token->surrounding_context,
			&input[end_index_in_line],
			ft_min(input_line_length - end_index_in_line,
				MAX_TRAILING_CONTEXT_LENGTH));
	if (token->context_was_truncated
		|| input_line_length - end_index_in_line > MAX_TRAILING_CONTEXT_LENGTH)
		ft_strcat(token->surrounding_context, "...");
}

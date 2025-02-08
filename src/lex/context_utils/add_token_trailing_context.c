/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_trailing_context.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:36:46 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:11:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "../lex.h"

void	add_token_trailing_context(
			char *context,
			const char *input,
			int end_index_in_line,
			int length_in_context)
{
	int	input_length;

	input_length = ft_strlen(input);
	if (length_in_context < MAX_TOKEN_LENGTH_IN_CONTEXT)
		ft_strncat(context,
			&input[end_index_in_line],
			ft_min(input_length - end_index_in_line,
				MAX_TRAILING_CONTEXT_LENGTH));
	if (length_in_context >= MAX_LEADING_CONTEXT_LENGTH
		|| input_length - end_index_in_line > MAX_LEADING_CONTEXT_LENGTH)
		ft_strcat(context, "...");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_leading_context.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:50:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 06:16:51 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "../lex.h"

void	add_token_leading_context(
			t_token *token,
			const char *input,
			int start_index_in_line)
{
	if (start_index_in_line > MAX_LEADING_CONTEXT_LENGTH)
		ft_strcat(token->surrounding_context, "...");
	ft_strncat(token->surrounding_context,
		&input[ft_max(start_index_in_line - MAX_LEADING_CONTEXT_LENGTH, 0)],
		ft_min(start_index_in_line, MAX_LEADING_CONTEXT_LENGTH));
}

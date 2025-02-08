/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_leading_context.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:50:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:11:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "../lex.h"

void	add_token_leading_context(
			char *context,
			const char *input,
			int start_index_in_line)
{
	if (start_index_in_line > MAX_LEADING_CONTEXT_LENGTH)
		ft_strcat(context, "...");
	ft_strncat(context,
		&input[ft_max(start_index_in_line - MAX_LEADING_CONTEXT_LENGTH, 0)],
		ft_min(start_index_in_line, MAX_LEADING_CONTEXT_LENGTH));
}

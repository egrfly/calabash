/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_start_index_in_context.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:40:19 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:15:02 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "../lex.h"

int	get_token_start_index_in_context(
		int start_index_in_line)
{
	int	start_index_in_context;

	start_index_in_context = 0;
	if (start_index_in_line > MAX_LEADING_CONTEXT_LENGTH)
		start_index_in_context += ELLIPSIS_LENGTH;
	start_index_in_context
		+= ft_min(start_index_in_line, MAX_LEADING_CONTEXT_LENGTH);
	return (start_index_in_context);
}

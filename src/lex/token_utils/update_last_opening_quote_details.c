/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_opening_quote_details.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:59:50 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 15:01:36 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "../lex.h"

void	update_last_opening_quote_details(
			t_input_tracker *input_tracker,
			t_token *token)
{
	if (token->content.word)
		token->last_opening_quote_line_start_index_in_word_content
			= ft_strlen(token->content.word);
	if (token->start_line_index != input_tracker->line_index)
		token->last_opening_quote_index_in_word_content_line
			= input_tracker->index_in_line;
	else
		token->last_opening_quote_index_in_word_content_line
			= input_tracker->index_in_line - token->start_index_in_start_line;
	token->last_opening_quote_line_index = input_tracker->line_index;
	token->last_opening_quote_index_in_line = input_tracker->index_in_line;
}

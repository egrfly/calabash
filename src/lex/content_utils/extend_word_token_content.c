/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_word_token_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:32:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:26:59 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_string.h"
#include "../lex.h"
#include "../token_utils/token_utils.h"

void	extend_word_token_content(
			t_input_tracker *input_tracker,
			t_token *token,
			bool *has_error)
{
	char	*existing_word;
	char	*extension_of_word;

	existing_word = token->content.word;
	extension_of_word
		= ft_strrange(input_tracker->input,
			get_token_start_index_in_current_line(input_tracker->line_index,
				token->start_line_index,
				token->start_index_in_start_line),
			input_tracker->index_in_line);
	token->content.word = ft_strjoin(token->content.word, extension_of_word);
	if (!token->content.word)
		*has_error = true;
	free(existing_word);
	free(extension_of_word);
}

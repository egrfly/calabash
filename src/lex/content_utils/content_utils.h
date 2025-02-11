/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:04:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 20:11:06 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTENT_UTILS_H
# define CONTENT_UTILS_H

# define NO_BACKSLASH_ADJUSTMENT 0

# include <stdbool.h>
# include "../lex.h"

void	extend_word_token_content(
			t_input_tracker *input_tracker,
			t_token *token,
			int backslash_adjustment,
			bool *has_error);
void	add_newline_to_word_token_content(
			t_token *token,
			bool *has_error);
int		get_operator_token_content(
			char *input,
			int start_index,
			int chars_count);
bool	some_operator_starts_with_chars(
			char *input,
			int start_index,
			int chars_count);

#endif

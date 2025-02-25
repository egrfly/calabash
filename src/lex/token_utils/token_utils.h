/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:27:10 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 19:36:02 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include <stdbool.h>
# include "../lex.h"

bool	advance_to_new_word_token_if_necessary(
			t_input_tracker *input_tracker,
			t_token **last_token,
			t_tokens_with_status *tokens_with_status);
bool	start_token(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_token *(*create_token_of_correct_type)(
				t_input_tracker *input_tracker,
				bool *out_of_memory));
bool	continue_token(
			t_input_tracker *input_tracker,
			t_token *last_token,
			bool (*is_valid_token_continuation)(
				t_input_tracker *input_tracker,
				t_token *last_token));
int		get_token_start_index_in_current_line(
			int current_line_index,
			int start_line_index,
			int start_index_in_start_line);
t_token	*get_last_token(
			t_list *tokens);
void	delimit_last_token_if_exists(
			t_input_tracker *input_tracker,
			t_token *token,
			bool *out_of_memory);

#endif

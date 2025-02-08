/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:27:10 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 06:00:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include <stdbool.h>
# include "../lex.h"

bool	start_token(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_token *(*create_token_of_correct_type)(
				t_input_tracker *input_tracker,
				bool *has_error),
			bool *has_error);
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
			bool *has_error);

#endif

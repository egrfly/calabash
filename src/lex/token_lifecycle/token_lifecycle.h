/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lifecycle.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:17:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 11:47:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIFECYCLE_H
# define TOKEN_LIFECYCLE_H

# include <stdbool.h>
# include "../lex.h"

t_token	*create_word_token(
			t_input_tracker *input_tracker,
			bool *out_of_memory);
t_token	*create_operator_token(
			t_input_tracker *input_tracker,
			bool *out_of_memory);
t_token	*create_whitespace_token(
			t_input_tracker *input_tracker,
			bool *out_of_memory);
t_token	*create_end_of_input_token(
			t_input_tracker *input_tracker,
			bool *out_of_memory);
t_token	*create_token(
			t_input_tracker *input_tracker,
			bool (*set_type_specific_properties)(
				t_token *token),
			bool *out_of_memory);
void	destroy_token(
			t_token *token);

#endif

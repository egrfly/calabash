/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lifecycle.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:17:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 06:26:25 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIFECYCLE_H
# define TOKEN_LIFECYCLE_H

# include <stdbool.h>
# include "../lex.h"

t_token	*create_word_token(
			t_input_tracker *input_tracker,
			bool *has_error);
t_token	*create_operator_token(
			t_input_tracker *input_tracker,
			bool *has_error);
t_token	*create_whitespace_token(
			t_input_tracker *input_tracker,
			bool *has_error);
t_token	*create_end_of_input_token(
			t_input_tracker *input_tracker,
			bool *has_error);
t_token	*create_token(
			t_input_tracker *input_tracker,
			bool (*set_type_specific_properties)(
				t_token *token),
			bool *has_error);
void	destroy_token(
			t_token *token);

#endif

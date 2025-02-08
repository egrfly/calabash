/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:09:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:57:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_UTILS_H
# define CONTEXT_UTILS_H

# define BLANK_TOKEN_LENGTH_IN_CONTEXT 3
# define MAX_TOKEN_LENGTH_IN_CONTEXT 10
# define MAX_LEADING_CONTEXT_LENGTH 5
# define MAX_TRAILING_CONTEXT_LENGTH 5
# define ELLIPSIS_LENGTH 3

# include "../lex.h"

void	add_to_token_context_if_space_available(
			t_input_tracker *input_tracker,
			t_token *token);
void	add_token_leading_context(
			char *context,
			const char *input,
			int start_index_in_line);
void	add_token_trailing_context(
			char *context,
			const char *input,
			int end_index_in_line,
			int length_in_context);
int		get_token_start_index_in_context(
			int start_index_in_line);

#endif

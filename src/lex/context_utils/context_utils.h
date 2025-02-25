/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:09:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 19:17:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_UTILS_H
# define CONTEXT_UTILS_H

# include "../lex.h"

void	add_to_token_context_and_advance(
			t_input_tracker *input_tracker,
			t_token *token);
void	add_token_leading_context(
			t_token *token,
			const char *input,
			int start_index_in_line);
void	add_token_trailing_context(
			t_token *token,
			const char *input,
			int end_index_in_line);
int		get_token_start_index_in_context(
			int start_index_in_line);
void	handle_newline_in_token_context(
			t_input_tracker *input_tracker,
			t_token *token);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:40:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 19:08:17 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include <stdbool.h>
# include "../../lex/lex.h"

int		get_post_token_line_index(
			t_token *token);
bool	token_is_of_type(
			t_token *token,
			t_token_type type);
void	set_token_type(
			t_token *token,
			t_token_type type);
void	consume_token(
			t_token *token);
void	mark_token_as_unsupported(
			t_token *token);
void	join_tokens(
			t_list_node *current_token_node,
			t_tokens_with_status *next_line_tokens);

#endif

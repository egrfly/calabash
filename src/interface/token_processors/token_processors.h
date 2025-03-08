/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:30:21 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 04:18:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_PROCESSORS_H
# define TOKEN_PROCESSORS_H

# include "../../lex/lex.h"
# include "../interface.h"

int		process_tokens(
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options,
			t_program_vars *program_vars);
t_token	*get_first_unsupported_token(
			t_list *tokens);
t_token	*get_first_unconsumed_token(
			t_list *tokens);

#endif

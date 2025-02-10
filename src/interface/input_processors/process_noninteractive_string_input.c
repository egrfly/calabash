/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_noninteractive_string_input.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:33:31 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lex/lex.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"

int	process_noninteractive_string_input(char *input, char *program_name)
{
	t_multiline_options		multiline_options;
	t_tokens_with_status	*tokens_with_status;

	multiline_options.input_mode_is_interactive = false;
	multiline_options.get_next_line = get_null_line;
	multiline_options.get_next_line_arg = NULL;
	tokens_with_status
		= lex(input,
			&multiline_options,
			DEFAULT_START_LINE_INDEX);
	return (process_tokens(
			tokens_with_status,
			&multiline_options,
			program_name));
}

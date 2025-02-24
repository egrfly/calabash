/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_noninteractive_string_input.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/24 12:33:40 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../lex/lex.h"
#include "../interface.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"
#include "./input_processors.h"

int	process_noninteractive_string_input(char *input, char *program_name)
{
	char					**input_lines;
	t_multiline_options		multiline_options;
	t_tokens_with_status	*tokens_with_status;

	input_lines = ft_split(input, "\n");
	if (!input_lines)
		return (ft_dprintf(STDERR_FILENO,
				"%s: out of memory\n",
				program_name), GENERAL_FAILURE);
	access_input_lines(SET, input_lines);
	multiline_options.input_mode_is_interactive = false;
	multiline_options.get_next_line
		= noninteractive_get_next_line_from_split_string;
	multiline_options.get_next_line_arg = NO_ARG;
	tokens_with_status
		= lex(noninteractive_get_next_line_from_split_string(NO_ARG),
			&multiline_options,
			DEFAULT_START_LINE_INDEX);
	return (process_tokens(
			tokens_with_status,
			&multiline_options,
			program_name));
}

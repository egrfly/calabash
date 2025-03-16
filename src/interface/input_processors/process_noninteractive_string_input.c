/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_noninteractive_string_input.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/11 00:59:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../interface.h"
#include "../line_getters/line_getters.h"
#include "../program_property_utils/program_property_utils.h"
#include "../token_processors/token_processors.h"

int	process_noninteractive_string_input(
		char *input,
		t_program_vars *program_vars)
{
	t_multiline_options		multiline_options;
	t_tokens_with_status	*tokens_with_status;
	int						exit_status;

	multiline_options.input_mode_is_interactive = false;
	multiline_options.get_next_line = noninteractive_get_null_line;
	multiline_options.get_next_line_arg = NO_ARG;
	tokens_with_status = lex(input, &multiline_options,
			DEFAULT_LINE_INDEX);
	exit_status = process_tokens(tokens_with_status, &multiline_options,
			program_vars);
	return (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_noninteractive_file_input.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 15:32:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "../../main.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"
#include "../interface.h"

int	process_noninteractive_file_input(
		int fd,
		t_program_vars *program_vars)
{
	t_multiline_options		multiline_options;
	char					*input;
	t_tokens_with_status	*tokens_with_status;
	int						exit_status;

	multiline_options.input_mode_is_interactive = false;
	multiline_options.get_next_line
		= noninteractive_get_next_line_from_file_descriptor;
	multiline_options.get_next_line_arg = &fd;
	input = ft_getline(fd);
	if (input)
	{
		tokens_with_status = lex(input, &multiline_options, DEFAULT_LINE_INDEX);
		exit_status = process_tokens(tokens_with_status, &multiline_options,
				program_vars);
		return (exit_status);
	}
	return (GENERAL_FAILURE);
}

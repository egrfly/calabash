/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_noninteractive_file_input.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 20:38:09 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"
#include "../interface.h"

int	process_noninteractive_file_input(
		int fd,
		t_program_name_and_env *program_name_and_env)
{
	t_multiline_options		multiline_options;
	char					*input;
	int						exit_status;
	t_tokens_with_status	*tokens_with_status;

	multiline_options.input_mode_is_interactive = false;
	multiline_options.get_next_line
		= noninteractive_get_next_line_from_file_descriptor;
	multiline_options.get_next_line_arg = &fd;
	input = ft_getline(fd);
	if (input)
	{
		tokens_with_status = lex(input, &multiline_options, DEFAULT_LINE_INDEX);
		exit_status = process_tokens(tokens_with_status, &multiline_options,
				program_name_and_env);
		return (destroy_tokens_with_status(tokens_with_status), exit_status);
	}
	return (GENERAL_FAILURE);
}

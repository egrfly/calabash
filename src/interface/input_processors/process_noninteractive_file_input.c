/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_noninteractive_file_input.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:35:33 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "../../lex/lex.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"
#include "../interface.h"

int	process_noninteractive_file_input(int fd, char *program_name)
{
	t_multiline_options		multiline_options;
	char					*input;
	t_tokens_with_status	*tokens_with_status;

	multiline_options.input_mode_is_interactive = false;
	multiline_options.get_next_line = noninteractive_get_next_line;
	multiline_options.get_next_line_arg = &fd;
	input = ft_getline(fd);
	if (input)
	{
		tokens_with_status
			= lex(input,
				&multiline_options,
				DEFAULT_START_LINE_INDEX);
		return (process_tokens(
				tokens_with_status,
				&multiline_options,
				program_name));
	}
	return (GENERAL_FAILURE);
}

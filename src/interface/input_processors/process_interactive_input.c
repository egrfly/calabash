/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_interactive_input.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/27 21:49:00 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../lex/lex.h"
#include "../interface.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"
#include "./input_processors.h"

static void	print_banner_if_available(void)
{
	int		banner_file_fd;
	char	*banner_file_line;

	banner_file_fd = open("calabash.txt", O_RDONLY);
	if (banner_file_fd > -1)
	{
		banner_file_line = ft_getline(banner_file_fd);
		while (banner_file_line)
		{
			ft_printf("%s\n", banner_file_line);
			free(banner_file_line);
			banner_file_line = ft_getline(banner_file_fd);
		}
		close(banner_file_fd);
	}
}

int	process_interactive_input(
		char *program_name,
		char **envp)
{
	t_multiline_options		multiline_options;
	char					*input;
	t_tokens_with_status	*tokens_with_status;
	int						latest_return_value;

	multiline_options.input_mode_is_interactive = true;
	multiline_options.get_next_line
		= interactive_get_next_line_from_standard_input;
	multiline_options.get_next_line_arg = NO_ARG;
	print_banner_if_available();
	latest_return_value = 0;
	while (true)
	{
		input = readline("\033[32mcalabash\033[36m>\033[0m ");
		if (!input)
			break ;
		tokens_with_status
			= lex(input, &multiline_options, DEFAULT_START_LINE_INDEX);
		latest_return_value
			= process_tokens(
				tokens_with_status, &multiline_options, program_name, envp);
	}
	ft_printf("\n");
	return (latest_return_value);
}

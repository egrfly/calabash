/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_interactive_input.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 08:34:40 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"
#include "ft_stdio.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../interface.h"
#include "input_processors.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"
#include "../../execute/signals/signals.h"
#include "../../execute/signals/readline_related/readline_related.h"

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

/* NORMINETTE: function too long! */
int	process_interactive_input(
		t_program_name_and_env *program_name_and_env)
{
	t_multiline_options		multiline_options;
	char					*input;
	t_tokens_with_status	*tokens_with_status;
	int						latest_exit_code;

	setup_signals();
	terminal_disable_echoctl(true);
	multiline_options.input_mode_is_interactive = true;
	multiline_options.get_next_line
		= interactive_get_next_line_from_standard_input;
	multiline_options.get_next_line_arg = NO_ARG;
	print_banner_if_available();
	latest_exit_code = SUCCESS;
	while (true)
	{
		input = readline("\033[32mcalabash\033[36m>\033[0m ");
		command_history_update_if_suitable(input, DO_NO_CLEANUP);
		if (!input)
			break ;
		tokens_with_status = lex(input, &multiline_options, DEFAULT_LINE_INDEX);
		if (g_signal != SIGNAL_FOR_CTRL_C)
		{
			latest_exit_code = process_tokens(tokens_with_status,
					&multiline_options, program_name_and_env);
		}
		destroy_tokens_with_status(tokens_with_status);
		set_global_signal_as_processed();
	}
	terminal_disable_echoctl(false);
	command_history_update_if_suitable(NULL, DO_CLEANUP);
	ft_printf("exit\n");
	return (latest_exit_code);
}

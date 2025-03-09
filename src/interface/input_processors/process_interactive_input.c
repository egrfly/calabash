/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_interactive_input.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 21:31:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_stdio.h"
#include "../../main.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../../execute/signals/signals.h"
#include "../interface.h"
#include "../command_history_utils/command_history_utils.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"

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

static void	enter_interactive_mode(
				t_multiline_options *multiline_options)
{
	multiline_options->input_mode_is_interactive = true;
	multiline_options->get_next_line
		= interactive_get_next_line_from_standard_input;
	multiline_options->get_next_line_arg = NO_ARG;
	install_signal_handlers();
	toggle_terminal_echoctl_suppression(true);
	print_banner_if_available();
}

static void	exit_interactive_mode(void)
{
	toggle_terminal_echoctl_suppression(false);
	access_command_history(DELETE, NO_ARG);
	ft_printf("exit\n");
}

int	process_interactive_input(
		t_program_vars *program_vars)
{
	t_multiline_options		multiline_options;
	char					*input;
	t_tokens_with_status	*tokens_with_status;
	int						latest_exit_code;

	enter_interactive_mode(&multiline_options);
	latest_exit_code = SUCCESS;
	while (true)
	{
		input = readline("\033[32mcalabash\033[36m>\033[0m ");
		access_command_history(SET, input);
		if (!input)
			break ;
		tokens_with_status = lex(input, &multiline_options, DEFAULT_LINE_INDEX);
		if (g_signal != SIGINT)
			latest_exit_code = process_tokens(tokens_with_status,
					&multiline_options, program_vars);
		else
			latest_exit_code = SIGNAL_BASE + g_signal;
		mark_global_signal_as_processed();
	}
	exit_interactive_mode();
	return (latest_exit_code);
}

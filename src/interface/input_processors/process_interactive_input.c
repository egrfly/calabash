/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_interactive_input.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/01 02:14:14 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* SIGNAL HANDLING - START */
#include <signal.h>
#include <termios.h>
/* SIGNAL HANDLING - END */
#include "ft_string.h"
#include "ft_stdio.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../interface.h"
#include "input_processors.h"
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

/* FUNCTIONS FOR SIGNAL HANDLING --- START */

volatile sig_atomic_t	global_signal;

void	terminal_disable_ECHOCTL(bool disable_ECHOCTL)
{
	static struct termios	original_settings;
	static struct termios	current_settings;
	static bool				initialized = false;

	if (!initialized)
		tcgetattr(STDIN_FILENO, &original_settings);
	ft_memcpy(&current_settings, &original_settings,
		sizeof(original_settings));
	if (disable_ECHOCTL)
		current_settings.c_lflag &= ~(ECHOCTL);
	else
		ft_memcpy(&current_settings, &original_settings,
			sizeof(original_settings));
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &current_settings);
}

void	ctrl_c_and_ctrl_backslash_handler(
		int signal_received, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	global_signal = signal_received;
	rl_on_new_line();
	rl_redisplay();
	if (signal_received == SIGNAL_FOR_CTRL_C)
	{
		ft_printf("^C");
		rl_replace_line("", 0);
	}
}

/* the last parameter may not make any sense? */
void	setup_signal_handler(
	int signal_received, void (*function_to_call)(), int block_signal_received)
{
	struct sigaction	sa;
	struct sigaction	sa_orig;

	ft_memset(&sa, 0x00, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (block_signal_received)
		sigaddset(&sa.sa_mask, signal_received);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = function_to_call;
	sigaction(signal_received, &sa, &sa_orig);
}

int	rl_waiting_for_input_event(void)
{
	if (global_signal == SIGNAL_FOR_CTRL_C)
		rl_done = true;
	return (0);
}

void	setup_signals(void)
{
	rl_event_hook = rl_waiting_for_input_event;
	setup_signal_handler(
		SIGNAL_FOR_CTRL_C, ctrl_c_and_ctrl_backslash_handler, false);
	setup_signal_handler(
		SIGNAL_FOR_CTRL_BACKSLASH,
		ctrl_c_and_ctrl_backslash_handler, false);
}

/* this function needs to be called from the multiline_options
 * as well? to cancel the more input ">_" prompt and get back
 * to the main "calabash>" prompt
 */
void	set_global_signal_as_processed(void)
{
	if (global_signal == SIGNAL_FOR_CTRL_C
		|| global_signal == SIGNAL_FOR_CTRL_BACKSLASH)
			global_signal = SIGNAL_PROCESSED;
}
/* FUNCTIONS FOR SIGNAL HANDLING --- END */

/* FUNCTIONS FOR COMMAND HISTORY --- START */
/* I'VE SEEN SOMEWHERE THAT IF input == "history -c"
 * THEN THE rl_clear_history() is called...
 * WHERE IS THE BEST WAY TO DO THIS? IN EXECUTION?
 */

/* BASH WILL ALSO ADD THE MULTILINE INPUT TO THE HISTORY
 * SO, 1st, BASH WILL ADD THE VERY 1ST PART OF THE MULTILINE,
 * THE PART THAT TRIGGERED THE MULTILINE TO START, THEN,
 * IF A SUCCESSFUL MULTILINE INPUT IS OBTAINED - EX, NO CTRL+C
 * WAS PRESSED - IT IS AGAIN ADDED TO THE HISTORY */
void	command_history_update_if_suitable(
			const char *input, bool perform_cleanup)
{
	static char	*last_input = NULL;

	if (perform_cleanup && last_input)
	{
		free(last_input);
		last_input = NULL;
		return ;
	}
	if (!input || (input && input[0] == '\0'))
		return ;
	if (last_input && ft_strcmp(last_input, input) == 0)
		return ;
	if (!last_input)
	{
		free(last_input);
		last_input = NULL;
	}
	last_input = ft_strdup(input);
	add_history(input);
}
/* FUNCTIONS FOR COMMAND HISTORY --- END */

/* NORMINETTE: too many functions in one file! */
/* NORMINETTE: function too long! */
int	process_interactive_input(
		char *program_name,
		char **envp)
{
	t_multiline_options		multiline_options;
	char					*input;
	t_tokens_with_status	*tokens_with_status;
	int						latest_return_value;

	setup_signals();
	terminal_disable_ECHOCTL(true);
	multiline_options.input_mode_is_interactive = true;
	multiline_options.get_next_line
		= interactive_get_next_line_from_standard_input;
	multiline_options.get_next_line_arg = NO_ARG;
	print_banner_if_available();
	latest_return_value = 0;
	while (true)
	{
		input = readline("\033[32mcalabash\033[36m>\033[0m ");
		command_history_update_if_suitable(input, DO_NO_CLEANUP);
		if (!input)
			break ;
		tokens_with_status
			= lex(input, &multiline_options, DEFAULT_START_LINE_INDEX);
		latest_return_value
			= process_tokens(
				tokens_with_status, &multiline_options, program_name, envp);
		destroy_tokens_with_status(tokens_with_status);
		set_global_signal_as_processed();
	}
	terminal_disable_ECHOCTL(false);
	command_history_update_if_suitable(NULL, DO_CLEANUP);
	ft_printf("\n");
	return (latest_return_value);
}

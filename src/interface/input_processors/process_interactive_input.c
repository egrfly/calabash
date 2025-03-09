/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_interactive_input.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 23:47:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_stdio.h"
#include "../../main.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../interface.h"
#include "../line_getters/line_getters.h"
#include "../token_processors/token_processors.h"

static void	print_banner_if_available(void)
{
	int		banner_file_fd;
	char	*banner_file_line;

	banner_file_fd = open("calabash.txt", O_RDONLY);
	if (banner_file_fd > -1)
	{
		ft_printf("----------------------------------------"
			"----------------------------------------\n");
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

#include "ft_string.h"
static void	update_command_prompt(char *prompt, int exit_code)
{
	char	*username;
	char	*hostname;
	char	*pwd;
	char	exit_code_string[4];

	// Change
	username = "Emily";
	hostname = "MacBook-Flynn";
	pwd = "/home/emily";
	ft_strcpy(prompt, "----------------------------------------"
		"----------------------------------------\n");
	if (pwd)
	{
		ft_strcat(prompt, "[\033[32m");
		if (ft_strlen(pwd) < 32)
			ft_strcat(prompt, pwd);
		else
		{
			ft_strcat(prompt, "...");
			ft_strcat(prompt, pwd + ft_strlen(pwd) - 32 + ELLIPSIS_LENGTH);
		}
		ft_strcat(prompt, "\033[0m]\n");
	}
	ft_strcat(prompt, "\033[36m");
	if (username)
	{
		if (ft_strlen(username) <= 16)
			ft_strcat(prompt, username);
		else
		{
			ft_strncat(prompt, username, 16 - ELLIPSIS_LENGTH);
			ft_strcat(prompt, "...");
		}
	}
	if (username && hostname)
		ft_strcat(prompt, "@");
	if (hostname)
	{
		if (ft_strlen(hostname) <= 16)
			ft_strcat(prompt, hostname);
		else
		{
			ft_strncat(prompt, hostname, 16 - ELLIPSIS_LENGTH);
			ft_strcat(prompt, "...");
		}
	}
	if (username || hostname)
		ft_strcat(prompt, " ");
	ft_strcat(prompt, "\033[32mcalabash\033[0m[");
	if (exit_code == SUCCESS)
		ft_strcat(prompt, "\033[32m");
	else
		ft_strcat(prompt, "\033[31m");
	exit_code_string[0] = (exit_code / 100) % 10 + '0';
	exit_code_string[1] = (exit_code / 10) % 10 + '0';
	exit_code_string[2] = (exit_code / 1) % 10 + '0';
	exit_code_string[3] = '\0';
	ft_strcat(prompt, exit_code_string);
	ft_strcat(prompt, "\033[0m]\033[36m>\033[0m ");
}

int	process_interactive_input(
		t_program_vars *program_vars)
{
	t_multiline_options		multiline_options;
	char					prompt[256];
	char					*input;
	t_tokens_with_status	*tokens_with_status;
	int						latest_exit_code;

	multiline_options.input_mode_is_interactive = true;
	multiline_options.get_next_line
		= interactive_get_next_line_from_standard_input;
	multiline_options.get_next_line_arg = NO_ARG;
	print_banner_if_available();
	latest_exit_code = SUCCESS;
	while (true)
	{
		update_command_prompt(prompt, latest_exit_code);
		input = readline(prompt);
		if (!input)
			break ;
		tokens_with_status = lex(input, &multiline_options, DEFAULT_LINE_INDEX);
		latest_exit_code = process_tokens(tokens_with_status,
				&multiline_options, program_vars);
	}
	ft_printf("\n");
	return (latest_exit_code);
}

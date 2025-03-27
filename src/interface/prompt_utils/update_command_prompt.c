/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_command_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:34:08 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/19 17:43:54 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "ft_string.h"
#include "../../main.h"
#include "../../lex/lex.h"
#include "./prompt_utils.h"

static void	update_command_prompt_with_cwd(
				char *prompt,
				char *cwd)
{
	ft_strcat(prompt, "[" ESC_GREEN);
	if (ft_strlen(cwd) < LONG_PROMPT_COMPONENT_MAX)
		ft_strcat(prompt, cwd);
	else
	{
		ft_strcat(prompt, "...");
		ft_strcat(prompt, ft_strchr(cwd, '\0')
			- LONG_PROMPT_COMPONENT_MAX
			+ ELLIPSIS_LENGTH);
	}
	ft_strcat(prompt, ESC_END "]\n");
}

static void	update_command_prompt_with_username(
				char *prompt,
				char *username)
{
	if (ft_strlen(username) <= SHORT_PROMPT_COMPONENT_MAX)
		ft_strcat(prompt, username);
	else
	{
		ft_strncat(prompt, username,
			SHORT_PROMPT_COMPONENT_MAX
			- ELLIPSIS_LENGTH);
		ft_strcat(prompt, "...");
	}
}

static void	update_command_prompt_with_hostname(
				char *prompt,
				char *hostname)
{
	if (ft_strlen(hostname) <= SHORT_PROMPT_COMPONENT_MAX)
		ft_strcat(prompt, hostname);
	else
	{
		ft_strncat(prompt, hostname,
			SHORT_PROMPT_COMPONENT_MAX
			- ELLIPSIS_LENGTH);
		ft_strcat(prompt, "...");
	}
}

static void	update_command_prompt_with_exit_status(
				char *prompt,
				int exit_status)
{
	static char	exit_status_string[EXIT_STATUS_LENGTH_MAX + 1];

	ft_strcat(prompt, "[");
	if (exit_status == SUCCESS)
		ft_strcat(prompt, ESC_GREEN);
	else
		ft_strcat(prompt, ESC_RED);
	exit_status_string[0] = (exit_status / 100) % 10 + '0';
	exit_status_string[1] = (exit_status / 10) % 10 + '0';
	exit_status_string[2] = (exit_status / 1) % 10 + '0';
	exit_status_string[3] = '\0';
	ft_strcat(prompt, exit_status_string);
	ft_strcat(prompt, ESC_END "]");
}

void	update_command_prompt(
			char *prompt,
			int exit_status,
			t_program_vars *program_vars)
{
	static char	username[SHORT_PROMPT_COMPONENT_MAX + 1];
	static char	hostname[SHORT_PROMPT_COMPONENT_MAX + 1];
	static char	cwd[PATH_MAX];

	get_short_prompt_component(username, (char *[]){"id", "-un", NULL},
		program_vars);
	get_short_prompt_component(hostname, (char *[]){"hostname", "-s", NULL},
		program_vars);
	ft_strcpy(prompt, "----------------------------------------"
		"----------------------------------------\n");
	if (getcwd(cwd, PATH_MAX))
		update_command_prompt_with_cwd(prompt, cwd);
	ft_strcat(prompt, ESC_CYAN);
	if (username[0])
		update_command_prompt_with_username(prompt, username);
	if (username[0] && hostname[0])
		ft_strcat(prompt, "@");
	if (hostname[0])
		update_command_prompt_with_hostname(prompt, hostname);
	ft_strcat(prompt, ESC_END);
	if (username[0] || hostname[0])
		ft_strcat(prompt, " ");
	ft_strcat(prompt, ESC_GREEN "calabash" ESC_END);
	update_command_prompt_with_exit_status(prompt, exit_status);
	ft_strcat(prompt, ESC_CYAN ">" ESC_END " ");
}

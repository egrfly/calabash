/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_command_history.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:53:27 by aistok            #+#    #+#             */
/*   Updated: 2025/03/14 13:50:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_string.h"
#include "../../main.h"
#include "../interface.h"

static void	access_command_history(
				t_access_mode mode,
				char *input)
{
	static char	*last_input = NULL;

	if (mode == DELETE)
	{
		rl_clear_history();
		free(last_input);
		last_input = NULL;
		return ;
	}
	if (mode == SET)
	{
		if (!input
			|| !ft_strlen(input)
			|| (last_input && !ft_strcmp(input, last_input)))
			return ;
		if (last_input)
			free(last_input);
		last_input = ft_strdup(input);
		add_history(input);
	}
}

void	clear_command_history(void)
{
	access_command_history(DELETE, NO_ARG);
}

void	add_last_command(
			char *input)
{
	access_command_history(SET, input);
}

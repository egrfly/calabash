/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c_and_ctrl_backslash_handler.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:32:58 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 15:12:07 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <readline/readline.h>
#include "ft_stdio.h"
#include "./signals.h"

void	ctrl_c_and_ctrl_backslash_handler(
	int signal_received, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	g_signal = signal_received;
	if (!rl_done)
	{
		rl_on_new_line();
		rl_redisplay();
		if (signal_received == SIGNAL_FOR_CTRL_C)
		{
			ft_printf("^C");
			rl_replace_line("", 0);
		}
	}
	else
	{
		if (signal_received == SIGNAL_FOR_CTRL_C)
			ft_printf("^C\n");
		if (signal_received == SIGNAL_FOR_CTRL_BACKSLASH)
			ft_printf("^\\Quit (core dumped)\n");
	}
}

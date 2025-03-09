/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_and_sigquit_handler.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:32:58 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 15:12:07 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include "ft_stdio.h"
#include "./signals.h"

void	sigint_and_sigquit_handler(
			int signal_received, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	g_signal = signal_received;
	if (!rl_done)
	{
		rl_on_new_line();
		rl_redisplay();
		if (signal_received == SIGINT)
		{
			ft_printf("^C");
			rl_replace_line("", 0);
		}
	}
	else
	{
		if (signal_received == SIGINT)
			ft_printf("^C\n");
		if (signal_received == SIGQUIT)
			ft_printf("^\\Quit\n");
	}
}

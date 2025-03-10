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
#include <stdio.h>
#include <readline/readline.h>
#include "ft_stdio.h"
#include "./signals.h"

void	sigint_handler(
			int signal_received,
			siginfo_t *info,
			void *ucontext)
{
	(void)signal_received;
	(void)info;
	(void)ucontext;
	g_signal = SIGINT;
	if (!rl_done)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_printf("^C");
		rl_replace_line("", 0);
	}
}
